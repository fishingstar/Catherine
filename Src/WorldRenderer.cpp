#include "WorldRenderer.h"
#include "IDevice.h"
#include "IWorld.h"
#include "WorldContext.h"
#include "CameraContext.h"
#include "LightContext.h"
#include "RenderContext.h"
#include "IMaterial.h"
#include "IVertexArray.h"
#include "glm/glm.hpp"

namespace Catherine
{
	extern IDevice * g_Device;

	bool WorldRenderer::Initialize()
	{
		// TODO : get device context cache to reduce useless state changes
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
		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			// collect render context
			m_Worlds[i]->Render();

			// extract context
			const WorldContext * tmp_context = m_Worlds[i]->GetWorldContext();
			const CameraContext * tmp_camera = tmp_context->GetCameraContext();
			const RenderContext * tmp_skybox = tmp_context->GetSkyboxRenderContext();
			const std::vector<RenderContext *> & tmp_renderContexts = tmp_context->GetRenderContexts();

			// clear screen
			const glm::vec3 & tmp_color = tmp_camera->GetClearColor();
			g_Device->ClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
			g_Device->Clear();

			// render commands
			for (size_t i = 0; i < tmp_renderContexts.size(); i++)
			{
				const RenderContext * tmp_renderContext = tmp_renderContexts[i];

				// material
				IMaterial * tmp_material = tmp_renderContext->GetMaterial();
				tmp_material->SetCommonUniform(tmp_context);
				tmp_material->Use();

				// vertex buffer
				IVertexArray * tmp_vertexArray = tmp_renderContext->GetVertexArray();
				tmp_vertexArray->Bind();

				// draw command
				g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);

				tmp_vertexArray->UnBind();
			}

			// render skybox
			IMaterial * tmp_material = tmp_skybox->GetMaterial();
			tmp_material->SetMat4x4("view", glm::mat4x4(glm::mat3x3(tmp_camera->GetViewMatrix())));
			tmp_material->SetMat4x4("projection", tmp_camera->GetProjectionMatrix());
			tmp_material->Use();

			IVertexArray * tmp_vertexArray = tmp_skybox->GetVertexArray();
			
			tmp_vertexArray->Bind();
			g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);
			tmp_vertexArray->UnBind();
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
}
