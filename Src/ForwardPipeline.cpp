#include "ForwardPipeline.h"
#include "WorldContext.h"
#include "CameraContext.h"
#include "LightContext.h"
#include "RenderContext.h"
#include "IMaterial.h"
#include "IDevice.h"
#include "IVertexArray.h"
#include "RenderTarget.h"
#include <algorithm>

namespace Catherine
{
	extern IDevice * g_Device;

	bool ForwardPipeline::Initialize()
	{
		m_RenderTarget_Back = new RenderTarget();
		m_RenderTarget_Back->Initialize(1280, 720, 0, false, false);
		m_RenderTarget_Shadow = new RenderTarget();
		m_RenderTarget_Shadow->Initialize(1280, 720, 1, true, true);

		return true;
	}

	void ForwardPipeline::Uninitialize()
	{

	}

	void ForwardPipeline::Render(const WorldContext * context)
	{
		// render shadow map
		RenderShadow(context);
		// render opaque primitives
		RenderOpaque(context);
		// render transparent primitives
		RenderTransparent(context);
	}

	void ForwardPipeline::RenderShadow(const WorldContext * context)
	{
		m_RenderTarget_Shadow->Use();

		// render shadow map

		m_RenderTarget_Back->Use();
	}

	void ForwardPipeline::RenderOpaque(const WorldContext * context)
	{
		const CameraContext * tmp_camera = context->GetCameraContext();
		const LightContext * tmp_light = context->GetLightContext();
		std::vector<RenderContext *> tmp_renderContexts = context->GetRenderContexts();
		
		// clear screen
		const glm::vec3 & tmp_color = tmp_camera->GetClearColor();
		g_Device->ClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
		g_Device->Clear();

		// sort commands
		std::stable_sort(tmp_renderContexts.begin(), tmp_renderContexts.end(),
			[](const RenderContext * left, const RenderContext * right) -> bool
			{
				bool tmp_reuslt = false;

				IMaterial * leftMaterial = left->GetMaterial();
				IMaterial * rightMaterial = right->GetMaterial();
				if (leftMaterial && rightMaterial)
				{
					if (leftMaterial->GetRenderPriority() < rightMaterial->GetRenderPriority())
					{
						tmp_reuslt = true;
					}
				}

				return tmp_reuslt;
			}
		);

		// render commands
		for (size_t i = 0; i < tmp_renderContexts.size(); i++)
		{
			const RenderContext * tmp_renderContext = tmp_renderContexts[i];

			// material
			IMaterial * tmp_material = tmp_renderContext->GetMaterial();
			tmp_material->SetCameraUniform(tmp_camera);
			tmp_material->SetLightUniform(tmp_light);
			tmp_material->Use();

			// vertex buffer
			IVertexArray * tmp_vertexArray = tmp_renderContext->GetVertexArray();
			tmp_vertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);

			tmp_vertexArray->UnBind();
		}
	}

	void ForwardPipeline::RenderTransparent(const WorldContext * context)
	{

	}
}