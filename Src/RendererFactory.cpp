#include <RendererFactory.h>
#include <WorldRenderer.h>

namespace Catherine
{
	RendererFactory * RendererFactory::Instance()
	{
		static RendererFactory s_instance;
		return &s_instance;
	}

	WorldRenderer * RendererFactory::CreateWorldRenderer()
	{
		WorldRenderer * tmp_renderer = new WorldRenderer();
		return tmp_renderer;
	}

	void RendererFactory::DeleteRenderer(IRenderer * renderer)
	{
		if (renderer != nullptr)
		{
			delete renderer;
		}
	}
}
