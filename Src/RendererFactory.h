#pragma once

namespace Catherine
{
	class IRenderer;

	class RendererFactory
	{
	public:
		static RendererFactory * Instance();

		IRenderer * CreateWorldRenderer();
		void DeleteRenderer(IRenderer * renderer);

	private:
		RendererFactory() { }
	};
}
