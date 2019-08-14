#pragma once

#include <stdint.h>
#include <vector>

namespace Catherine
{
	class IRenderTarget;

	class RenderTargetManager
	{
	public:
		static RenderTargetManager * Instance();

		IRenderTarget * GetDefaultRenderTarget();

		IRenderTarget * CreateRenderTarget(uint32_t width, uint32_t height, uint8_t color_count, bool depth, bool stencil);
		void DeleteRenderTarget(IRenderTarget * rt);

	private:
		RenderTargetManager() { }

	private:
		IRenderTarget * m_DefaultRenderTarget = nullptr;
		std::vector<IRenderTarget *> m_RenderTargets;
	};
}