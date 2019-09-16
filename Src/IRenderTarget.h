#pragma once

#include <stdint.h>
#include "DeviceCommon.h"

namespace Catherine
{
	class ITexture;

	class IRenderTarget
	{
	public:
		virtual ~IRenderTarget() { }

		virtual bool Initialize(uint32_t width, uint32_t height, uint8_t color_count, bool depth, bool stencil) = 0;
		virtual void Uninitialize() = 0;

		virtual ITexture * GetColorAttachment(uint8_t index) const = 0;
		virtual ITexture * GetDepthAttachment() const = 0;
		virtual ITexture * GetStencilAttachment() const = 0;

		virtual void Bind(RenderTargetUsage usage = RenderTargetUsage::Default) = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
	};
}