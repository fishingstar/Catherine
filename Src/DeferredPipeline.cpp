#include "DeferredPipeline.h"
#include "RenderTargetManager.h"
#include "DeviceConst.h"
#include "IRenderTarget.h"
#include "WorldContext.h"
#include "CameraContext.h"
#include "LightContext.h"
#include "RenderContext.h"
#include "IDevice.h"
#include "IMaterial.h"
#include "IVertexArray.h"
#include "Material.h"
#include <algorithm>

namespace Catherine
{
	extern IDevice * g_Device;

	const char * s_GeometryMaterial = "./res/material/geometry.mtl";

	DeferredPipeline::~DeferredPipeline()
	{

	}

	bool DeferredPipeline::Initialize()
	{
		m_RenderTarget_Back = RenderTargetManager::Instance()->GetDefaultRenderTarget();
		m_RenderTarget_Geometry = RenderTargetManager::Instance()->CreateRenderTarget(m_RenderTarget_Back->GetWidth(), m_RenderTarget_Back->GetHeight(), 3, true, false);

		m_GeometryMaterial = new Material();
		m_GeometryMaterial->Initialize(s_GeometryMaterial);

		return true;
	}

	void DeferredPipeline::Uninitialize()
	{

	}

	void DeferredPipeline::Render(const WorldContext * context)
	{
		// 1st render shadowmap
		RenderShadow(context);
		// 2nd render geometry
		RenderGeometry(context);
		// 3rd render opaque
		RenderLighting(context);
		// 4th render transparent
		RenderTransparent(context);
	}

	void DeferredPipeline::RenderShadow(const WorldContext * context)
	{

	}

	void DeferredPipeline::RenderGeometry(const WorldContext * context)
	{
		m_RenderTarget_Geometry->Use();
		{
			const CameraContext * tmp_camera = context->GetCameraContext();
			const LightContext * tmp_light = context->GetLightContext();
			std::vector<RenderContext *> tmp_renderContexts = context->GetRenderContexts();

			// clear screen
			const glm::vec3 & tmp_color = tmp_camera->GetClearColor();
			g_Device->SetClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
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

			m_GeometryMaterial->SetCameraUniform(tmp_camera);
			m_GeometryMaterial->SetLightUniform(tmp_light);
			m_GeometryMaterial->Use();

			// render commands
			for (size_t i = 0; i < tmp_renderContexts.size(); i++)
			{
				const RenderContext * tmp_renderContext = tmp_renderContexts[i];

				// material
				m_GeometryMaterial->SetModelUniform(tmp_renderContext);

				// vertex buffer
				IVertexArray * tmp_vertexArray = tmp_renderContext->GetVertexArray();
				tmp_vertexArray->Bind();

				// draw command
				g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);

				tmp_vertexArray->UnBind();
			}
		}
		m_RenderTarget_Back->Use();
	}

	void DeferredPipeline::RenderLighting(const WorldContext * context)
	{

	}

	void DeferredPipeline::RenderTransparent(const WorldContext * context)
	{

	}
}