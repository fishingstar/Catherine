#pragma once

#include "IPostProcess.h"

namespace Catherine
{
	class IMaterial;
	class ISampler;
	// temp code
	class IVertexArray;

	class Bloom : public IPostProcess
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void Process(IRenderTarget * src, IRenderTarget * dst) override;

	private:
		void RenderBloomArea(IRenderTarget * src, IRenderTarget * dst);
		void RenderBloomBlurHorizontal(IRenderTarget * src, IRenderTarget * dst);
		void RenderBloomBlurVertical(IRenderTarget* src, IRenderTarget* dst);
		void RenderBloomResult(IRenderTarget * src, IRenderTarget * origin, IRenderTarget * dst);

	private:
		IRenderTarget * m_PingRenderTarget = nullptr;
		IRenderTarget * m_PongRenderTarget = nullptr;

		IMaterial * m_BloomMaterial = nullptr;
		ISampler * m_BloomSampler = nullptr;

		IVertexArray * m_ScreenVertexArray;
	};
}