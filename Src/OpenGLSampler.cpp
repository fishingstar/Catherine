#include "OpenGLSampler.h"
#include "OpenGLCommon.h"

namespace Catherine
{
	bool OpenGLSampler::Initialize()
	{
		glGenSamplers(1, &m_Sampler);
		return true;
	}

	void OpenGLSampler::Uninitialize()
	{
		glDeleteSamplers(1, &m_Sampler);
	}

	void OpenGLSampler::SetWrapS(const WrapMode mode)
	{
		GLenum tmp_mode = OpenGLCommon::GetOpenGLWrapMode(mode);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_S, tmp_mode);
	}

	void OpenGLSampler::SetWrapT(const WrapMode mode)
	{
		GLenum tmp_mode = OpenGLCommon::GetOpenGLWrapMode(mode);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_T, tmp_mode);
	}

	void OpenGLSampler::SetWrapR(const WrapMode mode)
	{
		GLenum tmp_mode = OpenGLCommon::GetOpenGLWrapMode(mode);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_WRAP_R, tmp_mode);
	}

	void OpenGLSampler::SetMinFilter(const Filter filter)
	{
		GLenum tmp_filter = OpenGLCommon::GetOpenGLFilter(filter);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_MIN_FILTER, tmp_filter);
	}

	void OpenGLSampler::SetMagFilter(const Filter filter)
	{
		GLenum tmp_filter = OpenGLCommon::GetOpenGLFilter(filter);
		glSamplerParameteri(m_Sampler, GL_TEXTURE_MAG_FILTER, tmp_filter);
	}

	void OpenGLSampler::SetBorderColor(const float * data)
	{
		glSamplerParameterfv(m_Sampler, GL_TEXTURE_BORDER_COLOR, data);
	}

	void OpenGLSampler::Bind(const uint8_t slot)
	{
		glBindSampler(slot, m_Sampler);
	}
}