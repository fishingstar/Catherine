#include "OpenGLTexture.h"

namespace Catherine
{
	bool OpenGLTexture::Initialize(int width, int height, PixelFormat inner_format, PixelFormat format, ValueType value_type, void ** data)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		GLenum tmp_inner_format = OpenGLCommon::GetOpenGLPixelFormat(inner_format);
		GLenum tmp_format = OpenGLCommon::GetOpenGLPixelFormat(format);
		GLenum tmp_type = OpenGLCommon::GetOpenGLType(value_type);
		glTexImage2D(GL_TEXTURE_2D, 0, tmp_inner_format, width, height, 0, tmp_format, tmp_type, data[0]);
		//glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void OpenGLTexture::Uninitialize()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void OpenGLTexture::Use(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
}
