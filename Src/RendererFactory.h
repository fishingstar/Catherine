#pragma once

namespace Catherine
{
	class IRenderer;
	class WorldRenderer;

	class RendererFactory
	{
	public:
		static RendererFactory * Instance();

		WorldRenderer * CreateWorldRenderer();
		void DeleteRenderer(IRenderer * renderer);

	private:
		RendererFactory() { }
	};
}
