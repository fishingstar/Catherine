#pragma once

#include "IPipeline.h"

namespace Catherine
{
	class DeferredPipeline : public IPipeline
	{
	public:
		virtual ~DeferredPipeline() override { }

		virtual bool Initialize() override { }
		virtual void Uninitialize() override { }

		virtual void Render(const WorldContext * context) override { }
	};
}