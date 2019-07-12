#include <Material.h>
#include <IDevice.h>
#include <IProgram.h>
#include <ITexture.h>
#include <string>
#include <WorldContext.h>
#include <CameraContext.h>
#include <LightContext.h>

#include <WorldRenderer.h>
#include <Light.h>

namespace Catherine
{
	extern IDevice * g_Device;

	bool Material::Initialize(const char * param_Config)
	{
		m_Program = g_Device->CreateProgram();
		m_Program->AttachShader("./res/shader/simple.vs", "./res/shader/simple.fs");
		m_Program->Compile();
		m_Program->Link();

		return true;
	}

	void Material::SetInt(const char * key, int value)
	{
		m_Program->SetInt(key, value);
	}

	void Material::SetFloat(const char * key, float value)
	{
		m_Program->SetFloat(key, value);
	}

	void Material::SetVec2(const char * key, const glm::vec2 & value)
	{
		m_Program->SetVec2(key, value);
	}

	void Material::SetVec3(const char * key, const glm::vec3 & value)
	{
		m_Program->SetVec3(key, value);
	}

	void Material::SetVec4(const char * key, const glm::vec4 & value)
	{
		m_Program->SetVec4(key, value);
	}

	void Material::SetMat4x4(const char * key, const glm::mat4x4 & value)
	{
		m_Program->SetMat4x4(key, value);
	}

	void Material::SetTexture(const char * key, ITexture * value)
	{
		unsigned int tmp_slot = m_Slot++;
		m_Program->SetInt(key, tmp_slot);
		m_Textures.push_back(std::pair<unsigned int, ITexture *>(tmp_slot, value));
	}

	void Material::SetCommonUniform(const WorldContext * context)
	{
		const CameraContext * tmp_cameraContext = context->GetCameraContext();

		const glm::vec3 & tmp_cameraPos = tmp_cameraContext->GetPosition();
		const glm::mat4x4 & tmp_view = tmp_cameraContext->GetViewMatrix();
		const glm::mat4x4 & tmp_projection = tmp_cameraContext->GetProjectionMatrix();

		SetMat4x4("model", glm::mat4x4(1));
		SetMat4x4("view", tmp_view);
		SetMat4x4("projection", tmp_projection);
		SetVec3("viewPos", tmp_cameraPos);
		SetFloat("ambient", 0.2f);

		// TODO: LightContext in the future
		const glm::vec4 & tmp_lightColor = WorldRenderer::m_DirLight->GetLightColor();
		const glm::vec3 & tmp_lightDir = glm::vec3(0.3f, -0.3f, -0.6f);
		SetVec3("dirLight.lightDir", tmp_lightDir);
		SetVec4("dirLight.lightColor", tmp_lightColor);

		for (auto i = 0; i < 4; i++)
		{
			const glm::vec4 & tmp_pointColor = WorldRenderer::m_PointLight[i]->GetLightColor();
			const glm::vec3 & tmp_pointPos = WorldRenderer::m_PointLight[i]->GetPosition();
			float tmp_constant = WorldRenderer::m_PointLight[i]->GetAttenuationConstant();
			float tmp_linear = WorldRenderer::m_PointLight[i]->GetAttenuationLinear();
			float tmp_quadratic = WorldRenderer::m_PointLight[i]->GetAttenuationQuadratic();

			std::string tmp_key;
			std::string tmp_index = "pointLight[" + std::to_string(i) + "]";
			tmp_key = tmp_index + ".lightPos";
			SetVec3(tmp_key.c_str(), tmp_pointPos);
			tmp_key = tmp_index + ".lightColor";
			SetVec4(tmp_key.c_str(), tmp_pointColor);
			tmp_key = tmp_index + ".constant";
			SetFloat(tmp_key.c_str(), tmp_constant);
			tmp_key = tmp_index + ".linear";
			SetFloat(tmp_key.c_str(), tmp_linear);
			tmp_key = tmp_index + ".quadratic";
			SetFloat(tmp_key.c_str(), tmp_quadratic);
		}

		const glm::vec4 tmp_spotColor = WorldRenderer::m_SpotLight->GetLightColor();
		const glm::vec3 tmp_spotPos = WorldRenderer::m_SpotLight->GetPosition();
		const glm::vec3 tmp_spotDir = glm::vec3(0.0f, 0.0f, -1.0f);
		float tmp_constant = WorldRenderer::m_SpotLight->GetAttenuationConstant();
		float tmp_linear = WorldRenderer::m_SpotLight->GetAttenuationLinear();
		float tmp_quadratic = WorldRenderer::m_SpotLight->GetAttenuationQuadratic();
		SetVec3("spotLight.lightPos", tmp_spotPos);
		SetVec4("spotLight.lightColor", tmp_spotColor);
		SetVec3("spotLight.lightDir", tmp_spotDir);
		SetFloat("spotLight.innerCutoff", glm::cos(glm::radians(45.0f)));
		SetFloat("spotLight.outerCutoff", glm::cos(glm::radians(60.0f)));
		SetFloat("spotLight.constant", tmp_constant);
		SetFloat("spotLight.linear", tmp_linear);
		SetFloat("spotLight.quadratic", tmp_quadratic);
	}

	void Material::Use()
	{
		g_Device->EnableDepthTest(m_DepthTestEnabled);
		g_Device->SetDepthTestMode(m_DepthTestMode);

		g_Device->EnableCullFace(m_CullFaceEnabled);
		g_Device->SetCullFaceMode(m_CullFaceMode);

		for (size_t i = 0; i < m_Textures.size(); i++)
		{
			std::pair<unsigned int, ITexture *> tmp_pair = m_Textures[i];
			tmp_pair.second->Use(tmp_pair.first);
		}

		m_Program->Use();
	}
}