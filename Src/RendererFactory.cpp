#include <RendererFactory.h>
#include <Renderer.h>
#include <DemoRenderer.h>

namespace Catherine
{
	RendererFactory * RendererFactory::Instance()
	{
		static RendererFactory s_instance;
		return &s_instance;
	}

	IRenderer * RendererFactory::CreateWorldRenderer()
	{
		//IRenderer * tmp_renderer = new Renderer();
		IRenderer * tmp_renderer = new DemoRenderer();
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
