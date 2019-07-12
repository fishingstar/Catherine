#include <LightContext.h>

namespace Catherine
{
	LightContext::LightContext()
	{
		// directional light context
		m_DirectionContext = new DirectionalContext();

		// spot light context
		m_SpotContext = new SpotContext();

		// point light context
		for (unsigned int i = 0; i < POINT_LIGHT_COUNT; i++)
			m_PointContext[i] = new PointContext();
	}

	LightContext::~LightContext()
	{
		if (m_DirectionContext)
		{
			delete m_DirectionContext;
			m_DirectionContext = nullptr;
		}

		if (m_SpotContext)
		{
			delete m_SpotContext;
			m_SpotContext = nullptr;
		}

		for (unsigned int i = 0; i < POINT_LIGHT_COUNT; i++)
		{
			if (m_PointContext[i])
			{
				delete m_PointContext[i];
				m_PointContext[i] = nullptr;
			}
		}
	}
}