#pragma once

#include <ITexture.h>
#include <glad/glad.h>

namespace Catherine
{
	class OpenGLTexture : public ITexture
	{
	public:
		virtual bool Initialize(int width, int height, PixelFormat format, void * data = nullptr) override;
		virtual void Uninitialize() override;
		virtual void Use(unsigned int slot) override;

	private:
		GLuint m_Texture = 0;
	};
}
