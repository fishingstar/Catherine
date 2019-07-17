#include "OpenGLTexture.h"

namespace Catherine
{
	bool OpenGLTexture::Initialize(int width, int height, PixelFormat format, void * data)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLenum tmp_format = OpenGLCommon::GetOpenGLPixelFormat(format);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, tmp_format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

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
