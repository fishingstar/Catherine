#pragma once

#include "ITexture.h"
#include "glad/glad.h"

namespace Catherine
{
	class OpenGLTexture : public ITexture
	{
	public:
		virtual bool Initialize(int width, int height, PixelFormat inner_format, PixelFormat format, ValueType value_type, void ** data = nullptr) override;
		virtual void Uninitialize() override;
		virtual void Use(unsigned int slot) override;

	public:
		GLuint GetResource() const { return m_Texture; }

	private:
		GLuint m_Texture = 0;
	};
}
