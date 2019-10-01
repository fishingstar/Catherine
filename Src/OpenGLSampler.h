#pragma once

#include "ISampler.h"
#include "glad/glad.h"

namespace Catherine
{
	class OpenGLSampler : public ISampler
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void SetWrapS(const WrapMode mode) override;
		virtual void SetWrapT(const WrapMode mode) override;
		virtual void SetWrapR(const WrapMode mode) override;
		virtual void SetMinFilter(const Filter filter) override;
		virtual void SetMagFilter(const Filter filter) override;
		virtual void SetBorderColor(const float* data) override;

		virtual void Bind(const uint8_t slot) override;

	private:
		GLenum m_Sampler = GL_NONE;
	};
}