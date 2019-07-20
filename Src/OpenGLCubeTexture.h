#pragma once

#include "ITexture.h"

namespace Catherine
{
	class OpenGLCubeTexture : public ITexture
	{
	public:
		virtual bool Initialize(int width, int height, PixelFormat format, void ** data = nullptr) override;
		virtual void Uninitialize() override;
		virtual void Use(unsigned int slot) override;

	private:
		GLuint m_Texture = 0;
	};
}