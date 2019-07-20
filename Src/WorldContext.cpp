#include "WorldContext.h"

namespace Catherine
{
	void WorldContext::AddRenderContext(RenderContext * context)
	{
		if (context != nullptr)
		{
			m_RenderContexts.push_back(context);
		}
	}

	void WorldContext::Clear()
	{
		m_CameraContext = nullptr;
		m_LightContext = nullptr;
		m_RenderContexts.clear();
	}
}