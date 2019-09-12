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



		struct ScreenVertex
		{
			glm::vec3 Position;
			glm::vec2 Texcoord;
		};

		std::vector<ScreenVertex> tmp_vertexBuffer = 
		{
			{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
			{ glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
			{ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
			{ glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }
		};

		std::vector<uint32_t> tmp_indexBuffer = 
		{
			0, 1, 2,
			0, 2, 3
		};

		m_ScreenVertexArray = g_Device->CreateVertexArray();
		m_ScreenVertexArray->Bind();

		std::vector<AttributeLayout> tmp_attributes;
		tmp_attributes.emplace_back(0, 3, ValueType::Float, false, sizeof(ScreenVertex), 0);
		tmp_attributes.emplace_back(1, 2, ValueType::Float, false, sizeof(ScreenVertex), 3 * sizeof(float));
		auto tmp_vertex = g_Device->CreateVertexBuffer(sizeof(ScreenVertex) * tmp_vertexBuffer.size(), Usage::Static_Draw, &tmp_vertexBuffer[0], tmp_attributes);
		// only support 4 byte(32bit) stride index for now, 2 byte(16bit) in the future
		auto tmp_index = g_Device->CreateIndexBuffer(4, sizeof(uint32_t) * tmp_indexBuffer.size(), Usage::Static_Draw, &tmp_indexBuffer[0]);

		m_ScreenVertexArray->UnBind();
		m_ScreenVertexArray->SetVertexCount(tmp_vertexBuffer.size());
		m_ScreenVertexArray->SetIndexCount(tmp_indexBuffer.size());

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
		// 4th render forward
		//RenderForward(context);
		// 5th render transparent
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

			// render commands
			for (size_t i = 0; i < tmp_renderContexts.size(); i++)
			{
				const RenderContext * tmp_renderContext = tmp_renderContexts[i];

				// material
				IMaterial * tmp_material = tmp_renderContext->GetMaterial();
				if (tmp_material->IsForwardInDerferredPath())
					continue;

				tmp_material->SetModelUniform(tmp_renderContext);
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
	}

	void DeferredPipeline::RenderLighting(const WorldContext * context)
	{
		m_RenderTarget_Back->Use();
		{
			const CameraContext * tmp_camera = context->GetCameraContext();
			const LightContext * tmp_light = context->GetLightContext();

			// clear screen
			const glm::vec3 & tmp_color = tmp_camera->GetClearColor();
			g_Device->SetClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
			g_Device->Clear();

			ITexture * tmp_diffuse = m_RenderTarget_Geometry->GetColorAttachment(0);
			ITexture * tmp_normal = m_RenderTarget_Geometry->GetColorAttachment(1);
			ITexture * tmp_mask = m_RenderTarget_Geometry->GetColorAttachment(2);
			ITexture * tmp_depth = m_RenderTarget_Geometry->GetDepthAttachment();

			m_GeometryMaterial->SetTexture("GColor", tmp_diffuse);
			m_GeometryMaterial->SetTexture("GNormal", tmp_normal);
			m_GeometryMaterial->SetTexture("GMask", tmp_mask);
			m_GeometryMaterial->SetTexture("GDepth", tmp_depth);

			m_GeometryMaterial->SetCameraUniform(tmp_camera);
			m_GeometryMaterial->SetLightUniform(tmp_light);
			m_GeometryMaterial->Use();

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}

	void DeferredPipeline::RenderForward(const WorldContext * context)
	{
		m_RenderTarget_Back->Use();
		{
			const CameraContext * tmp_camera = context->GetCameraContext();
			const LightContext * tmp_light = context->GetLightContext();
			std::vector<RenderContext *> tmp_renderContexts = context->GetRenderContexts();

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
				if (tmp_material->IsForwardInDerferredPath())
				{
					tmp_material->SetModelUniform(tmp_renderContext);
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
		}
	}

	void DeferredPipeline::RenderTransparent(const WorldContext * context)
	{

	}
}