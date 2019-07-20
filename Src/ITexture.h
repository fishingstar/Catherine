#pragma once

#include "OpenGLCommon.h"

namespace Catherine
{
	class ITexture
	{
	public:
		virtual bool Initialize(int width, int height, PixelFormat format, void ** data = nullptr) = 0;
		virtual void Uninitialize() = 0;
		virtual void Use(unsigned int slot) = 0;
	};
}
