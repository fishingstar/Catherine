#include <WorldContext.h>

namespace Catherine
{
	void WorldContext::AddRenderContext(RenderContext * context)
	{
		if (context != nullptr)
		{
			m_RenderContexts.push_back(context);
		}
	}

	void WorldContext::ClearRenderContext()
	{
		m_RenderContexts.clear();
	}

	const std::vector<RenderContext *> & WorldContext::GetRenderContexts() const
	{
		return m_RenderContexts;
	}

	void WorldContext::SetCameraContext(CameraContext * context)
	{
		m_CameraContext = context;
	}

	void WorldContext::SetLightContext(LightContext * context)
	{
		m_LightContext = context;
	}
}