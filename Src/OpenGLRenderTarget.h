#pragma once

#include "IRenderTarget.h"
#include "glad/glad.h"
#include <vector>

namespace Catherine
{
	class ITexture;

	class OpenGLRenderTarget : public IRenderTarget
	{
	public:
		OpenGLRenderTarget();
		virtual ~OpenGLRenderTarget() override;

		virtual bool Initialize(uint32_t width, uint32_t height, uint8_t color_count, bool depth, bool stencil) override;
		virtual void Uninitialize() override;

		virtual ITexture * GetColorAttachment(uint8_t index) const override;
		virtual ITexture * GetDepthAttachment() const override;
		virtual ITexture * GetStencilAttachment() const override;

		virtual void Use() override;

	private:
		GLuint m_FrameBuffer = 0;

		std::vector<ITexture *> m_ColorAttachments;
		ITexture * m_DepthAttachment = nullptr;
		ITexture * m_StencilAttachment = nullptr;
		ITexture * m_DepthStencilAttachment = nullptr;
	};
}