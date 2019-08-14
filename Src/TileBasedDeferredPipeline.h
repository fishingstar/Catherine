#pragma once

#include "IPipeline.h"

namespace Catherine
{
	class TileBasedDeferredPipeline : public IPipeline
	{
	public:
		virtual ~TileBasedDeferredPipeline() override { }

		virtual bool Initialize() override { }
		virtual void Uninitialize() override { }

		virtual void Render(const WorldContext * context) override { }
	};
}