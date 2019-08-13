#include "OpenGLCubeTexture.h"

namespace Catherine
{
	bool OpenGLCubeTexture::Initialize(int width, int height, PixelFormat inner_format, PixelFormat format, ValueType value_type, void ** data)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		GLenum tmp_inner_format = OpenGLCommon::GetOpenGLPixelFormat(inner_format);
		GLenum tmp_format = OpenGLCommon::GetOpenGLPixelFormat(format);
		GLenum tmp_type = OpenGLCommon::GetOpenGLType(value_type);
		for (size_t i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, tmp_inner_format, width, height, 0, tmp_format, tmp_type, data[i]);
		}
		//glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		return true;
	}

	void OpenGLCubeTexture::Uninitialize()
	{
		glDeleteTextures(1, &m_Texture);
	}

	void OpenGLCubeTexture::Use(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	}
}