#pragma once

#include <IWorldContext.h>
#include <vector>

namespace Catherine
{
	class RenderContext;

	class WorldContext : public IWorldContext
	{
	public:

	private:
		// collected render context in levels
		std::vector<RenderContext *> m_RenderContexts;
	};
}