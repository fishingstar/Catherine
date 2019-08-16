#include "Material.h"
#include "IProgram.h"
#include "ITexture.h"
#include "CameraContext.h"
#include "LightContext.h"
#include "TextureManager.h"
#include "StateManager.h"
#include "ProgramManager.h"
#include "tinyxml2.h"
#include "LogUtility.h"

namespace Catherine
{
	bool Material::Initialize(const char * param_Config)
	{
		tinyxml2::XMLDocument doc;
		if (doc.LoadFile(param_Config) != tinyxml2::XML_SUCCESS)
		{
			LogError("Material::Initialize : LoadFile Failed...");
			return false;
		}

		tinyxml2::XMLElement * tmp_root = doc.FirstChildElement();

		// shader
		tinyxml2::XMLElement * tmp_shader = tmp_root->FirstChildElement("Shader");
		tinyxml2::XMLElement * tmp_vertex = tmp_shader->FirstChildElement("Vertex");
		tinyxml2::XMLElement * tmp_fragment = tmp_shader->FirstChildElement("Fragment");

		m_Program = ProgramManager::Instance()->GetProgram(tmp_vertex->GetText(), tmp_fragment->GetText());

		// texture
		tinyxml2::XMLElement * tmp_texture = tmp_root->FirstChildElement("Texture");
		if (tmp_texture)
		{
			tinyxml2::XMLElement * tmp_item = tmp_texture->FirstChildElement();
			while (tmp_item)
			{
				const char * tmp_key = tmp_item->Attribute("Key");
				const char * tmp_value = tmp_item->Attribute("Value");

				ITexture * tmp_resource = TextureManager::Instance()->GetTexture(tmp_value);
				if (tmp_resource)
				{
					SetTexture(tmp_key, tmp_resource);
				}

				tmp_item = tmp_item->NextSiblingElement();
			}
		}

		// cube texture
		tinyxml2::XMLElement * tmp_cubeTexture = tmp_root->FirstChildElement("CubeTexture");
		if (tmp_cubeTexture)
		{
			tinyxml2::XMLElement * tmp_cubeItem = tmp_cubeTexture->FirstChildElement();
			while (tmp_cubeItem)
			{
				std::vector<std::string> tmp_cubeTextures;
				const char * tmp_key = tmp_cubeItem->Attribute("Key");
				tmp_cubeTextures.push_back(tmp_cubeItem->Attribute("Right"));
				tmp_cubeTextures.push_back(tmp_cubeItem->Attribute("Left"));
				tmp_cubeTextures.push_back(tmp_cubeItem->Attribute("Top"));
				tmp_cubeTextures.push_back(tmp_cubeItem->Attribute("Bottom"));
				tmp_cubeTextures.push_back(tmp_cubeItem->Attribute("Front"));
				tmp_cubeTextures.push_back(tmp_cubeItem->Attribute("Back"));

				ITexture * tmp_resource = TextureManager::Instance()->GetCubeTexture(tmp_cubeTextures);
				if (tmp_resource)
				{
					SetTexture(tmp_key, tmp_resource);
				}

				tmp_cubeItem = tmp_cubeItem->NextSiblingElement();
			}
		}

		// param


		// state
		tinyxml2::XMLElement * tmp_stateRoot = tmp_root->FirstChildElement("RenderState");
		if (tmp_stateRoot)
		{
			tinyxml2::XMLElement * tmp_cullMode = tmp_stateRoot->FirstChildElement("CullFaceMode");
			if (tmp_cullMode)
			{
				m_CullFaceEnabled = tmp_cullMode->BoolAttribute("Enabled", true);
				m_CullFaceMode = (CullFaceMode)tmp_cullMode->IntAttribute("Value", 0);
			}

			tinyxml2::XMLElement * tmp_depthMode = tmp_stateRoot->FirstChildElement("DepthTestMode");
			if (tmp_depthMode)
			{
				m_DepthTestEnabled = tmp_depthMode->BoolAttribute("Enabled", true);
				m_DepthTestMode = (DepthTestMode)tmp_depthMode->IntAttribute("Value", 0);
			}

			tinyxml2::XMLElement * tmp_blendMode = tmp_stateRoot->FirstChildElement("BlendMode");
			if (tmp_blendMode)
			{
				m_BlendEnabled = tmp_blendMode->BoolAttribute("Enabled", true);
				m_SrcFunc = (BlendFunc)tmp_blendMode->IntAttribute("Src", 5);
				m_DstFunc = (BlendFunc)tmp_blendMode->IntAttribute("Dst", 5);
				m_SrcAlphaFunc = (BlendFunc)tmp_blendMode->IntAttribute("SrcAlpha", 5);
				m_DstAlphaFunc = (BlendFunc)tmp_blendMode->IntAttribute("DstAlpha", 5);
				m_BlendEquation = (BlendEquation)tmp_blendMode->IntAttribute("BlendEquation", 0);
			}
		}

		tinyxml2::XMLElement * tmp_priorityElement = tmp_root->FirstChildElement("RenderPriority");
		if (tmp_priorityElement)
		{
			m_RenderPriority = tmp_priorityElement->FloatText(2000.0f);
		}

		return true;
	}

	void Material::SetInt(const char * key, int value)
	{
		m_Program->Use();
		m_Program->SetInt(key, value);
	}

	void Material::SetFloat(const char * key, float value)
	{
		m_Program->Use();
		m_Program->SetFloat(key, value);
	}

	void Material::SetVec2(const char * key, const glm::vec2 & value)
	{
		m_Program->Use();
		m_Program->SetVec2(key, value);
	}

	void Material::SetVec3(const char * key, const glm::vec3 & value)
	{
		m_Program->Use();
		m_Program->SetVec3(key, value);
	}

	void Material::SetVec4(const char * key, const glm::vec4 & value)
	{
		m_Program->Use();
		m_Program->SetVec4(key, value);
	}

	void Material::SetMat4x4(const char * key, const glm::mat4x4 & value)
	{
		m_Program->Use();
		m_Program->SetMat4x4(key, value);
	}

	void Material::SetTexture(const char * key, ITexture * value)
	{
		m_Program->Use();
		unsigned int tmp_slot = m_Slot++;
		m_Program->SetInt(key, tmp_slot);
		m_Textures.push_back(std::pair<unsigned int, ITexture *>(tmp_slot, value));
	}

	void Material::SetCameraUniform(const CameraContext * context)
	{
		const glm::vec3 & tmp_cameraPos = context->GetPosition();
		const glm::mat4x4 & tmp_view = context->GetViewMatrix();
		const glm::mat4x4 & tmp_projection = context->GetProjectionMatrix();

		SetMat4x4("model", glm::mat4x4(1));
		SetMat4x4("view", tmp_view);
		SetMat4x4("projection", tmp_projection);
		SetVec3("viewPos", tmp_cameraPos);
	}

	void Material::SetLightUniform(const LightContext * context)
	{
		SetFloat("ambient", 0.2f);

		const LightContext::DirectionalContext * tmp_dirContext = context->GetDirectionContext();
		SetVec3("dirLight.lightDir", tmp_dirContext->m_Direction);
		SetVec4("dirLight.lightColor", tmp_dirContext->m_LightColor);

		for (unsigned int i = 0; i < LightContext::POINT_LIGHT_COUNT; i++)
		{
			const LightContext::PointContext * tmp_pointContext = context->GetPointConext(i);

			std::string tmp_key;
			std::string tmp_index = "pointLight[" + std::to_string(i) + "]";
			tmp_key = tmp_index + ".lightPos";
			SetVec3(tmp_key.c_str(), tmp_pointContext->m_Position);
			tmp_key = tmp_index + ".lightColor";
			SetVec4(tmp_key.c_str(), tmp_pointContext->m_LightColor);
			tmp_key = tmp_index + ".constant";
			SetFloat(tmp_key.c_str(), tmp_pointContext->m_AttenuationConstant);
			tmp_key = tmp_index + ".linear";
			SetFloat(tmp_key.c_str(), tmp_pointContext->m_AttenuationLinear);
			tmp_key = tmp_index + ".quadratic";
			SetFloat(tmp_key.c_str(), tmp_pointContext->m_AttenuationQuadratic);
		}

		const LightContext::SpotContext * tmp_spotContext = context->GetSpotContext();
		SetVec3("spotLight.lightPos", tmp_spotContext->m_Position);
		SetVec3("spotLight.lightDir", tmp_spotContext->m_Direction);
		SetVec4("spotLight.lightColor", tmp_spotContext->m_LightColor);
		SetFloat("spotLight.innerCutoff", glm::cos(glm::radians(45.0f)));
		SetFloat("spotLight.outerCutoff", glm::cos(glm::radians(60.0f)));
		SetFloat("spotLight.constant", tmp_spotContext->m_AttenuationConstant);
		SetFloat("spotLight.linear", tmp_spotContext->m_AttenuationLinear);
		SetFloat("spotLight.quadratic", tmp_spotContext->m_AttenuationQuadratic);
	}

	float Material::GetRenderPriority() const
	{
		return m_RenderPriority;
	}

	void Material::Use()
	{
		StateManager::Instance()->EnableDepthTest(m_DepthTestEnabled);
		StateManager::Instance()->SetDepthTestMode(m_DepthTestMode);

		StateManager::Instance()->EnableCullFace(m_CullFaceEnabled);
		StateManager::Instance()->SetCullFaceMode(m_CullFaceMode);

		StateManager::Instance()->EnableBlend(m_BlendEnabled);
		StateManager::Instance()->SetBlendEquation(m_BlendEquation);
		StateManager::Instance()->SetBlendFunc(m_SrcFunc, m_DstFunc, m_SrcAlphaFunc, m_DstAlphaFunc);

		for (size_t i = 0; i < m_Textures.size(); i++)
		{
			std::pair<unsigned int, ITexture *> tmp_pair = m_Textures[i];
			tmp_pair.second->Use(tmp_pair.first);
		}

		m_Program->Use();
	}
}