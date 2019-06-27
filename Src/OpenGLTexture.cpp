#include <OpenGLTexture.h>
#include <LogUtility.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Catherine
{
	void GLTexture::LoadFromFile(const char * param_Path)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width = 0;
		int height = 0;
		int channels = 0;

		unsigned char * tmp_data = stbi_load(param_Path, &width, &height, &channels, 0);
		if (tmp_data)
		{
			unsigned int tmp_format = channels == 4 ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, tmp_format, GL_UNSIGNED_BYTE, tmp_data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			LogError("GLTexture LoadFromFile Failed...");
		}

		stbi_image_free(tmp_data);
	}

	void GLTexture::Use(unsigned int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_Texture);
	}
}
