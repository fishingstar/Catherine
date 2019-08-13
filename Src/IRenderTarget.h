#pragma once

#include <stdint.h>

namespace Catherine
{
	class IRenderTarget
	{
	public:
		virtual ~IRenderTarget() { }

		virtual bool Initialize(uint32_t width, uint32_t height, uint8_t color_count, bool depth, bool stencil) = 0;
		virtual void Uninitialize() = 0;

		virtual void Use() = 0;
	};
}