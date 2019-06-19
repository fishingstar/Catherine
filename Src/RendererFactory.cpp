#include <RendererFactory.h>
#include <Renderer.h>

namespace Catherine
{
	RendererFactory * RendererFactory::Instance()
	{
		static RendererFactory s_instance;
		return &s_instance;
	}

	IRenderer * RendererFactory::CreateMainRenderer() const
	{
		IRenderer * tmp_renderer = new Renderer();
		return tmp_renderer;
	}
}
