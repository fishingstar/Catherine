#pragma once

#include "IPipeline.h"
#include "CameraContext.h"

namespace Catherine
{
	class WorldContext;
	class LightContext;
	class CameraContext;
	class IRenderTarget;
	class IMaterial;
	class ITexture;
	class ISampler;
	class IPostProcess;

	// TODO : remove vertexarray
	class IVertexArray;

	class DeferredPipeline : public IPipeline
	{
	public:
		virtual ~DeferredPipeline() override;

		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void Render(const WorldContext * context) override;

	private:
		void RenderShadow(const WorldContext * context);

		void RenderDeferred(const WorldContext * context);
		void RenderGeometry(const WorldContext * context);
		void RenderLighting(const WorldContext * context);

		void RenderForward(const WorldContext * context);
		void BlitDepthBuffer();
		void RenderOpaque(const WorldContext * context);
		void RenderTransparent(const WorldContext * context);

		void RenderPostProcess();

		CameraContext GenerateShadowCameraContext(const LightContext * light, const CameraContext * camera);

	private:
		// render target
		IRenderTarget * m_RenderTarget_Back = nullptr;
		IRenderTarget * m_RenderTarget_Geometry = nullptr;
		IRenderTarget * m_RenderTarget_Shadow = nullptr;
		IRenderTarget * m_RenderTarget_PostSrc = nullptr;
		IRenderTarget * m_RenderTarget_PostDst = nullptr;
		IRenderTarget * m_RenderTarget_Main = nullptr;

		// postprocess
		std::vector<IPostProcess *> m_PostProcessQueue;

		// internel texture and sampler
		ISampler * m_ShadowSampler = nullptr;
		ISampler * m_GBufferSampler = nullptr;

		ITexture * m_PrefilterMap = nullptr;
		ISampler * m_PrefilterSampler = nullptr;

		ITexture * m_BRDF_LUT = nullptr;
		ISampler * m_BRDF_LUTSampler = nullptr;

		// internel information
		CameraContext m_ShadowCameraContext;
		IMaterial* m_GeometryMaterial = nullptr;
		IVertexArray* m_ScreenVertexArray = nullptr;
	};
}