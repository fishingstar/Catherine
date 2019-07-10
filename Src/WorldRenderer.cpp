#include <WorldRenderer.h>
#include <Camera.h>
#include <Light.h>
#include <global.h>
#include <IWorld.h>
#include <WorldContext.h>
#include <RenderContext.h>
#include <IMaterial.h>
#include <IVertexArray.h>

namespace Catherine
{
	extern IDevice * g_Device;

	ICamera * WorldRenderer::m_Camera = nullptr;
	ILight * WorldRenderer::m_DirLight = nullptr;
	ILight * WorldRenderer::m_PointLight[4] = { nullptr };
	ILight * WorldRenderer::m_SpotLight = nullptr;

	bool WorldRenderer::Initialize()
	{
		m_Camera = new Camera();
		m_Camera->SetPosition(glm::vec3(6.0f, 15.0f, 6.0f));
		m_Camera->SetRotation(glm::vec3(45.0f, -45.0f, 0.0f));
		m_Camera->SetProjectionMode(ProjectionMode::Persperctive);
		m_Camera->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		CreateLights();

		g_Device->SetFrontFace(FrontFaceMode::CounterClockwise);

		return true;
	}

	void WorldRenderer::Uninitialize()
	{

	}

	void WorldRenderer::PreRender()
	{
		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			m_Worlds[i]->PreRender();
		}
	}

	void WorldRenderer::Render()
	{
		// TODO: pipeline
		const glm::vec3 & tmp_color = m_Camera->GetClearColor();
		g_Device->ClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
		g_Device->Clear();

		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			// collect render context
			m_Worlds[i]->Render();

			// render commands
			const WorldContext * tmp_context = m_Worlds[i]->GetWorldContext();
			const std::vector<RenderContext *> & tmp_renderContexts = tmp_context->GetRenderContexts();
			for (size_t i = 0; i < tmp_renderContexts.size(); i++)
			{
				RenderContext * tmp_renderContext = tmp_renderContexts[i];

				// material
				IMaterial * tmp_material = tmp_renderContext->GetMaterial();
				tmp_material->SetCommonUniform();
				tmp_material->Use();

				// vertex
				IVertexArray * tmp_vertexArray = tmp_renderContext->GetVertexArray();
				tmp_vertexArray->Bind();

				// draw command

				tmp_vertexArray->UnBind();
			}
		}
	}

	void WorldRenderer::PostRender()
	{
		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			m_Worlds[i]->PostRender();
		}
	}

	void WorldRenderer::RegisterWorld(IWorld * world)
	{
		if (world != nullptr)
		{
			m_Worlds.push_back(world);
		}
	}

	void WorldRenderer::CreateLights()
	{
		m_DirLight = new Light();
		m_DirLight->SetLightType(LightType::Directional);
		m_DirLight->SetLightColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		glm::vec3 tmp_pos[4] = {
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f)
		};

		glm::vec4 tmp_color[4] = {
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
			glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
		};

		for (auto i = 0; i < 4; i++)
		{
			m_PointLight[i] = new Light();
			m_PointLight[i]->SetLightType(LightType::Point);
			m_PointLight[i]->SetLightColor(tmp_color[i]);
			m_PointLight[i]->SetPosition(tmp_pos[i]);
		}

		m_SpotLight = new Light();
		m_SpotLight->SetLightType(LightType::Spot);
		m_SpotLight->SetLightColor(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f));
		m_SpotLight->SetPosition(glm::vec3(0.0f, 0.0f, 0.7f));
		m_SpotLight->SetRotation(glm::vec3(0.0f, 0.0f, 0.0f));
	}
}
