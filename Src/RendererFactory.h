#pragma once

namespace Catherine
{
	class IRenderer;

	class RendererFactory
	{
	public:
		static RendererFactory * Instance();

		IRenderer * CreateMainRenderer() const;

	private:
		RendererFactory() { }
	};
}
