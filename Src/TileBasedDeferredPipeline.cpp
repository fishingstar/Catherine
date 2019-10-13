#include "TileBasedDeferredPipeline.h"
#include "IDevice.h"
#include "IProgram.h"
#include "DeviceConst.h"
#include "RenderTargetManager.h"
#include "WorldContext.h"
#include "CameraContext.h"
#include "LightContext.h"
#include "RenderContext.h"
#include "IMaterial.h"
#include "IVertexArray.h"
#include "IRenderTarget.h"
#include "Material.h"
#include "ISampler.h"
#include "glm/gtc/type_ptr.hpp"
#include "TextureManager.h"
#include "Bloom.h"
#include "Exposure.h"
#include "ITexture.h"
#include "IStorageBuffer.h"

#include <algorithm>

namespace Catherine
{
	extern IDevice * g_Device;

	static const char * s_ComputeShader = "./res/shader/TBDRLight.cs";

	static const char * s_GeometryMaterial = "./res/material/geometry.mtl";

	static const std::vector<std::string> s_PrefilterPath =
	{
		"./res/skybox/day/right.jpg",
		"./res/skybox/day/left.jpg",
		"./res/skybox/day/top.jpg",
		"./res/skybox/day/bottom.jpg",
		"./res/skybox/day/back.jpg",
		"./res/skybox/day/front.jpg"
	};

	const std::string s_BRDF_LUT_Path = "./res/texture/ibl_brdf_lut.png";

	static const size_t s_TileWidth = DEFAULT_SCREEN_WIDTH / 16;
	static const size_t s_TileHeight = DEFAULT_SCREEN_HEIGHT / 16;

	TileBasedDeferredPipeline::~TileBasedDeferredPipeline()
	{

	}

	bool TileBasedDeferredPipeline::Initialize()
	{
		// post process
		IPostProcess * tmp_bloom = new Bloom();
		tmp_bloom->Initialize();
		m_PostProcessQueue.push_back(tmp_bloom);
		IPostProcess * tmp_exposure = new Exposure();
		tmp_exposure->Initialize();
		m_PostProcessQueue.push_back(tmp_exposure);

		m_RenderTarget_Back = RenderTargetManager::Instance()->GetDefaultRenderTarget();
		m_RenderTarget_Geometry = RenderTargetManager::Instance()->CreateRenderTarget(m_RenderTarget_Back->GetWidth(), m_RenderTarget_Back->GetHeight(), 3, true, false);
		m_RenderTarget_Shadow = RenderTargetManager::Instance()->CreateRenderTarget(2048, 2048, 0, true, false);
		if (m_PostProcessQueue.size() > 0)
		{
			m_RenderTarget_PostSrc = RenderTargetManager::Instance()->CreateRenderTarget(m_RenderTarget_Back->GetWidth(), m_RenderTarget_Back->GetHeight(), 1, true, false);
			m_RenderTarget_PostDst = RenderTargetManager::Instance()->CreateRenderTarget(m_RenderTarget_Back->GetWidth(), m_RenderTarget_Back->GetHeight(), 1, true, false);
			m_RenderTarget_Main = m_RenderTarget_PostSrc;
		}
		else
		{
			m_RenderTarget_Main = m_RenderTarget_Back;
		}

		m_GeometryMaterial = new Material();
		m_GeometryMaterial->Initialize(s_GeometryMaterial);

		m_ShadowSampler = g_Device->CreateSampler();
		m_ShadowSampler->SetMinFilter(Filter::Linear);
		m_ShadowSampler->SetMagFilter(Filter::Linear);
		m_ShadowSampler->SetWrapS(WrapMode::Clamp_To_Border);
		m_ShadowSampler->SetWrapT(WrapMode::Clamp_To_Border);
		m_ShadowSampler->SetBorderColor(glm::value_ptr(glm::vec4(1.0f)));

		m_GBufferSampler = g_Device->CreateSampler();
		m_GBufferSampler->SetMinFilter(Filter::Nearest);
		m_GBufferSampler->SetMagFilter(Filter::Nearest);
		m_GBufferSampler->SetWrapS(WrapMode::Clamp_To_Edge);
		m_GBufferSampler->SetWrapT(WrapMode::Clamp_To_Edge);

		m_PrefilterMap = TextureManager::Instance()->GetCubeTexture(s_PrefilterPath);
		m_PrefilterSampler = g_Device->CreateSampler();
		m_PrefilterSampler->SetMinFilter(Filter::Linear);
		m_PrefilterSampler->SetMagFilter(Filter::Linear);
		m_PrefilterSampler->SetWrapS(WrapMode::Clamp_To_Edge);
		m_PrefilterSampler->SetWrapT(WrapMode::Clamp_To_Edge);
		m_PrefilterSampler->SetWrapR(WrapMode::Clamp_To_Edge);

		m_BRDF_LUT = TextureManager::Instance()->GetTexture(s_BRDF_LUT_Path);
		m_BRDF_LUTSampler = g_Device->CreateSampler();
		m_BRDF_LUTSampler->SetMinFilter(Filter::Linear);
		m_BRDF_LUTSampler->SetMagFilter(Filter::Linear);
		m_BRDF_LUTSampler->SetWrapS(WrapMode::Clamp_To_Edge);
		m_BRDF_LUTSampler->SetWrapT(WrapMode::Clamp_To_Edge);

		// compute shader
		m_ComputeProgram = g_Device->CreateProgram();
		m_ComputeProgram->AttachComputeShader(s_ComputeShader);
		bool tmp_compileReuslt = m_ComputeProgram->Compile();
		if (!tmp_compileReuslt)
			return false;
		bool tmp_linkResult = m_ComputeProgram->Link();
		if (!tmp_linkResult)
			return false;

		const uint32_t MAX_POINT_LIGHT_COUNT = 4;
		const uint32_t MAX_SPOT_LIGHT_COUNT = 4;
		struct TileLightList
		{
			uint32_t PointLightCount;
			uint32_t PointLightIndices[MAX_POINT_LIGHT_COUNT];
			uint32_t SpotLightCount;
			uint32_t SpotLightIndices[MAX_SPOT_LIGHT_COUNT];
		};
		struct LightList
		{
			TileLightList tile[3600];
		};
		m_LightListBuffer = g_Device->CreateStorageBuffer(sizeof(LightList), Usage::Dynamic_Draw, nullptr);



		// temp code
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

	void TileBasedDeferredPipeline::Uninitialize()
	{

	}

	void TileBasedDeferredPipeline::Render(const WorldContext * context)
	{
		// 1st render shadowmap
		RenderShadow(context);
		// 2nd render geometry
		RenderDeferred(context);
		// 3th render forward
		RenderForward(context);
		// 4th render postprocess
		RenderPostProcess();
	}

	void TileBasedDeferredPipeline::RenderShadow(const WorldContext * context)
	{
		m_RenderTarget_Shadow->Bind();
		{
			const CameraContext* tmp_camera = context->GetCameraContext();
			const LightContext* tmp_light = context->GetLightContext();
			std::vector<RenderContext*> tmp_renderContexts = context->GetRenderContexts();

			m_ShadowCameraContext = GenerateShadowCameraContext(tmp_light, tmp_camera);

			// clear screen
			g_Device->Clear((BitField)BufferBit::Depth);

			// sort commands
			std::stable_sort(tmp_renderContexts.begin(), tmp_renderContexts.end(),
				[](const RenderContext* left, const RenderContext* right) -> bool
				{
					bool tmp_reuslt = false;

					IMaterial* leftMaterial = left->GetMaterial();
					IMaterial* rightMaterial = right->GetMaterial();
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
				const RenderContext* tmp_renderContext = tmp_renderContexts[i];
				IMaterial* tmp_material = tmp_renderContext->GetMaterial();

				// skip no shadow objects or material with no shadow pass
				if (!tmp_renderContext->GetCastShadow() || !tmp_material->HasPass(ShaderPass::Shadow))
					continue;

				// material
				tmp_material->SetModelUniform(tmp_renderContext);
				tmp_material->SetCameraUniform(&m_ShadowCameraContext);
				tmp_material->SetLightUniform(tmp_light);
				tmp_material->SetTexture("prefilterMap", m_PrefilterMap);
				tmp_material->SetSampler("prefilterMap", m_PrefilterSampler);
				tmp_material->SetTexture("brdfLUT", m_BRDF_LUT);
				tmp_material->SetSampler("brdfLUT", m_BRDF_LUTSampler);
				tmp_material->Use(ShaderPass::Shadow);

				// vertex buffer
				IVertexArray* tmp_vertexArray = tmp_renderContext->GetVertexArray();
				tmp_vertexArray->Bind();

				// draw command
				g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);

				tmp_vertexArray->UnBind();
			}
		}
	}

	void TileBasedDeferredPipeline::RenderDeferred(const WorldContext* context)
	{
		// 1st render geometry
		RenderGeometry(context);
		// 2nd compute light
		ComputeLight(context);
		// 3rd render shading
		RenderLighting(context);
	}

	void TileBasedDeferredPipeline::RenderGeometry(const WorldContext * context)
	{
		m_RenderTarget_Geometry->Bind();
		{
			const CameraContext* tmp_camera = context->GetCameraContext();
			const LightContext* tmp_light = context->GetLightContext();
			std::vector<RenderContext*> tmp_renderContexts = context->GetRenderContexts();

			// clear screen
			const glm::vec3& tmp_color = tmp_camera->GetClearColor();
			g_Device->SetClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
			g_Device->Clear((BitField)BufferBit::All);

			// sort commands
			std::stable_sort(tmp_renderContexts.begin(), tmp_renderContexts.end(),
				[](const RenderContext* left, const RenderContext* right) -> bool
				{
					bool tmp_reuslt = false;

					IMaterial* leftMaterial = left->GetMaterial();
					IMaterial* rightMaterial = right->GetMaterial();
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
				const RenderContext* tmp_renderContext = tmp_renderContexts[i];

				// material
				IMaterial* tmp_material = tmp_renderContext->GetMaterial();
				if (tmp_material->IsForwardInDerferredPath())
					continue;

				tmp_material->SetModelUniform(tmp_renderContext);
				tmp_material->SetCameraUniform(tmp_camera);
				tmp_material->SetLightUniform(tmp_light);
				tmp_material->SetShadowUniform(&m_ShadowCameraContext);
				tmp_material->SetTexture("shadowmap", m_RenderTarget_Shadow->GetDepthAttachment());
				tmp_material->SetSampler("shadowmap", m_ShadowSampler);
				tmp_material->Use(ShaderPass::Deferred);

				// vertex buffer
				IVertexArray* tmp_vertexArray = tmp_renderContext->GetVertexArray();
				tmp_vertexArray->Bind();

				// draw command
				g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);

				tmp_vertexArray->UnBind();
			}
		}
	}

	void TileBasedDeferredPipeline::ComputeLight(const WorldContext * context)
	{
		// compute shader and uniform
		m_ComputeProgram->Use();
		m_ComputeProgram->SetInt("GDepth", 0);

		// camera matrix
		const CameraContext * tmp_camera = context->GetCameraContext();
		const glm::mat4x4 & tmp_view = tmp_camera->GetViewMatrix();
		m_ComputeProgram->SetMat4x4("view", tmp_view);
		const glm::mat4x4 & tmp_projection = tmp_camera->GetProjectionMatrix();
		m_ComputeProgram->SetMat4x4("projection", tmp_projection);
		const glm::mat4x4 & tmp_invProjection = tmp_camera->GetProjectionMatrix();
		m_ComputeProgram->SetMat4x4("invProjection", glm::inverse(tmp_invProjection));

		// light info
		const LightContext * tmp_light = context->GetLightContext();
		for (unsigned int i = 0; i < LightContext::POINT_LIGHT_COUNT; i++)
		{
			const LightContext::PointContext * tmp_pointContext = tmp_light->GetPointConext(i);

			std::string tmp_key;
			std::string tmp_index = "pointLight[" + std::to_string(i) + "]";
			tmp_key = tmp_index + ".lightPos";
			m_ComputeProgram->SetVec3(tmp_key.c_str(), tmp_pointContext->m_Position);
			tmp_key = tmp_index + ".lightColor";
			m_ComputeProgram->SetVec4(tmp_key.c_str(), tmp_pointContext->m_LightColor);
			tmp_key = tmp_index + ".constant";
			m_ComputeProgram->SetFloat(tmp_key.c_str(), tmp_pointContext->m_AttenuationConstant);
			tmp_key = tmp_index + ".linear";
			m_ComputeProgram->SetFloat(tmp_key.c_str(), tmp_pointContext->m_AttenuationLinear);
			tmp_key = tmp_index + ".quadratic";
			m_ComputeProgram->SetFloat(tmp_key.c_str(), tmp_pointContext->m_AttenuationQuadratic);
		}

		// depth texture and sampler
		ITexture * tmp_depth = m_RenderTarget_Geometry->GetDepthAttachment();
		tmp_depth->Use(0);
		m_GBufferSampler->Bind(0);

		// storage buffer
		m_LightListBuffer->Bind(0);

		// dispatch
		g_Device->DispatchCompute(s_TileWidth, s_TileHeight, 1);
	}

	void TileBasedDeferredPipeline::RenderLighting(const WorldContext * context)
	{
		m_RenderTarget_Main->Bind();
		{
			const CameraContext* tmp_camera = context->GetCameraContext();
			const LightContext* tmp_light = context->GetLightContext();

			// clear screen
			const glm::vec3& tmp_color = tmp_camera->GetClearColor();
			g_Device->SetClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
			g_Device->Clear((BitField)BufferBit::All);

			ITexture* tmp_diffuse = m_RenderTarget_Geometry->GetColorAttachment(0);
			ITexture* tmp_normal = m_RenderTarget_Geometry->GetColorAttachment(1);
			ITexture* tmp_mask = m_RenderTarget_Geometry->GetColorAttachment(2);
			ITexture* tmp_depth = m_RenderTarget_Geometry->GetDepthAttachment();

			m_GeometryMaterial->SetTexture("GColor", tmp_diffuse);
			m_GeometryMaterial->SetSampler("GColor", m_GBufferSampler);
			m_GeometryMaterial->SetTexture("GNormal", tmp_normal);
			m_GeometryMaterial->SetSampler("GNormal", m_GBufferSampler);
			m_GeometryMaterial->SetTexture("GMask", tmp_mask);
			m_GeometryMaterial->SetSampler("GMask", m_GBufferSampler);
			m_GeometryMaterial->SetTexture("GDepth", tmp_depth);
			m_GeometryMaterial->SetSampler("GDepth", m_GBufferSampler);

			m_GeometryMaterial->SetTexture("prefilterMap", m_PrefilterMap);
			m_GeometryMaterial->SetSampler("prefilterMap", m_PrefilterSampler);
			m_GeometryMaterial->SetTexture("brdfLUT", m_BRDF_LUT);
			m_GeometryMaterial->SetSampler("brdfLUT", m_BRDF_LUTSampler);

			m_GeometryMaterial->SetCameraUniform(tmp_camera);
			m_GeometryMaterial->SetLightUniform(tmp_light);
			m_GeometryMaterial->Use(ShaderPass::Deferred);

			// light list
			m_LightListBuffer->Bind(0);

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}

	void TileBasedDeferredPipeline::RenderForward(const WorldContext* context)
	{
		// 1st blit depth buffer
		// TODO : no need to blit depth buffer if nothing need to be rendered in the following forward task
		BlitDepthBuffer();
		// 2nd render opaque
		RenderOpaque(context);
		// 3rd render transparent
		RenderTransparent(context);
	}

	void TileBasedDeferredPipeline::BlitDepthBuffer()
	{
		m_RenderTarget_Geometry->Bind(RenderTargetUsage::Read);
		m_RenderTarget_Main->Bind(RenderTargetUsage::Draw);
		g_Device->BlitFrameBuffer(
			0, 0, m_RenderTarget_Geometry->GetWidth(), m_RenderTarget_Geometry->GetHeight(),
			0, 0, m_RenderTarget_Main->GetWidth(), m_RenderTarget_Main->GetHeight(),
			(BitField)BufferBit::Depth, Filter::Nearest
		);
	}

	void TileBasedDeferredPipeline::RenderOpaque(const WorldContext* context)
	{
		m_RenderTarget_Main->Bind();
		{
			const CameraContext* tmp_camera = context->GetCameraContext();
			const LightContext* tmp_light = context->GetLightContext();
			std::vector<RenderContext*> tmp_renderContexts = context->GetRenderContexts();

			// sort commands
			std::stable_sort(tmp_renderContexts.begin(), tmp_renderContexts.end(),
				[](const RenderContext* left, const RenderContext* right) -> bool
				{
					bool tmp_reuslt = false;

					IMaterial* leftMaterial = left->GetMaterial();
					IMaterial* rightMaterial = right->GetMaterial();
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
				const RenderContext* tmp_renderContext = tmp_renderContexts[i];

				// material
				IMaterial* tmp_material = tmp_renderContext->GetMaterial();
				if (tmp_material->IsForwardInDerferredPath())
				{
					tmp_material->SetModelUniform(tmp_renderContext);
					tmp_material->SetCameraUniform(tmp_camera);
					tmp_material->SetLightUniform(tmp_light);
					tmp_material->Use(ShaderPass::Deferred);

					// vertex buffer
					IVertexArray* tmp_vertexArray = tmp_renderContext->GetVertexArray();
					tmp_vertexArray->Bind();

					// draw command
					g_Device->DrawElement(DrawMode::TRIANGLES, tmp_vertexArray->GetIndexCount(), ValueType::UInt, 0);

					tmp_vertexArray->UnBind();
				}
			}
		}
	}

	void TileBasedDeferredPipeline::RenderTransparent(const WorldContext* context)
	{

	}

	void TileBasedDeferredPipeline::RenderPostProcess()
	{
		IRenderTarget* tmp_src = m_RenderTarget_PostSrc;
		IRenderTarget* tmp_dst = m_RenderTarget_PostDst;
		IRenderTarget* tmp_temp = nullptr;

		for (size_t i = 0; i < m_PostProcessQueue.size(); ++i)
		{
			if (i == m_PostProcessQueue.size() - 1)
				tmp_dst = m_RenderTarget_Back;

			IPostProcess* tmp_process = m_PostProcessQueue[i];
			tmp_process->Process(tmp_src, tmp_dst);

			tmp_temp = tmp_src;
			tmp_src = tmp_dst;
			tmp_dst = tmp_src;
		}
	}

	CameraContext TileBasedDeferredPipeline::GenerateShadowCameraContext(const LightContext * light, const CameraContext * camera)
	{
		// get any view matrix of light
		auto tmp_dirContext = light->GetDirectionContext();
		glm::mat4x4 tmp_view = tmp_dirContext->GetDynamicViewMatrix(glm::vec3(0.0f, 0.0f, 0.0f));

		// transform to light space
		std::vector<glm::vec4> tmp_points = camera->GetFrustumPoints(0.0f, 50.0f);
		for (size_t i = 0; i < tmp_points.size(); ++i)
		{
			tmp_points[i] = tmp_view * tmp_points[i];
		}

		// calculate AABB box
		glm::vec4 tmp_minPoint = tmp_points[0];
		glm::vec4 tmp_maxPoint = tmp_points[0];
		for (size_t i = 1; i < tmp_points.size(); ++i)
		{
			tmp_minPoint = glm::min(tmp_minPoint, tmp_points[i]);
			tmp_maxPoint = glm::max(tmp_maxPoint, tmp_points[i]);
		}
		glm::vec3 tmp_center = (tmp_minPoint + tmp_maxPoint) / 2.0f;
		tmp_center.z = tmp_maxPoint.z;
		tmp_center = glm::inverse(tmp_view) * glm::vec4(tmp_center, 1.0f);

		// build new camera context
		CameraContext tmp_newContext;
		tmp_newContext.SetProjectionMode(ProjectionMode::Ortho);
		tmp_newContext.SetSize(tmp_maxPoint.y - tmp_minPoint.y);
		tmp_newContext.SetAspect((tmp_maxPoint.x - tmp_minPoint.x) / (tmp_maxPoint.y - tmp_minPoint.y)); // (camera->GetAspect());
		tmp_newContext.SetNearPlane(0.0f);
		tmp_newContext.SetFarPlane(tmp_maxPoint.z - tmp_minPoint.z);
		tmp_newContext.SetRotation(tmp_dirContext->m_Rotation);
		tmp_newContext.SetPosition(tmp_center);
		tmp_newContext.Apply();

		return tmp_newContext;
	}
}