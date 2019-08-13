#include "RenderTarget.h"
#include "OpenGLTexture.h"

namespace Catherine
{
	RenderTarget::RenderTarget()
	{

	}

	RenderTarget::~RenderTarget()
	{

	}

	bool RenderTarget::Initialize(uint32_t width, uint32_t height, uint8_t color_count, bool depth, bool stencil)
	{
		for (size_t i = 0; i < color_count; ++i)
		{
			ITexture * tmp_colorAttachment = new OpenGLTexture();
			void * tmp_data = nullptr;
			tmp_colorAttachment->Initialize(width, height, PixelFormat::A8R8G8B8, PixelFormat::A8R8G8B8, ValueType::UByte, &tmp_data);
			m_ColorAttachments.push_back(tmp_colorAttachment);
		}

		if (depth && stencil)
		{
			ITexture * tmp_depth_stencil = new OpenGLTexture();
			void * tmp_data = nullptr;
			tmp_depth_stencil->Initialize(width, height, PixelFormat::Depth24_Stencil8, PixelFormat::Depth_Stencil, ValueType::UInt_24_8, &tmp_data);
			m_DepthStencilAttachment = tmp_depth_stencil;
		}
		else if (depth)
		{
			ITexture * tmp_depth = new OpenGLTexture();
			void * tmp_data = nullptr;
			tmp_depth->Initialize(width, height, PixelFormat::Depth_Component, PixelFormat::Depth_Component, ValueType::Float, &tmp_data);
			m_DepthAttachment = tmp_depth;
		}
		else if (stencil)
		{
			ITexture * tmp_stencil = new OpenGLTexture();
			void * tmp_data = nullptr;
			tmp_stencil->Initialize(width, height, PixelFormat::Stencil_Index, PixelFormat::Stencil_Index, ValueType::UByte, &tmp_data);
			m_StencilAttachment = tmp_stencil;
		}

		if (color_count > 0 || depth || stencil)
		{
			glGenFramebuffers(1, &m_FrameBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

			for (size_t i = 0; i < m_ColorAttachments.size(); ++i)
			{
				OpenGLTexture * tmp_texture = (OpenGLTexture *)m_ColorAttachments[i];
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, tmp_texture->GetResource(), 0);
			}

			if (m_ColorAttachments.size() == 0)
			{
				glDrawBuffer(GL_NONE);
			}

			if (m_DepthStencilAttachment)
			{
				OpenGLTexture * tmp_texture = (OpenGLTexture *)m_DepthStencilAttachment;
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tmp_texture->GetResource(), 0);
			}
			else
			{
				if (m_DepthAttachment)
				{
					OpenGLTexture * tmp_texture = (OpenGLTexture *)m_DepthAttachment;
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tmp_texture->GetResource(), 0);
				}

				if (m_StencilAttachment)
				{
					OpenGLTexture * tmp_texture = (OpenGLTexture *)m_StencilAttachment;
					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, tmp_texture->GetResource(), 0);
				}
			}

			GLenum tmp_result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
			if (tmp_result != GL_FRAMEBUFFER_COMPLETE)
			{
				return false;
			}

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		return true;
	}

	void RenderTarget::Uninitialize()
	{

	}

	void RenderTarget::Use()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
	}
}