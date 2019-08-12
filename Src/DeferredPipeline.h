#pragma once

#include "IPipeline.h"

namespace Catherine
{
	class DeferredPipeline : public IPipeline
	{
	public:
		virtual ~DeferredPipeline() { }

		virtual bool Initialize() override { }
		virtual void Uninitialize() override { }
	};
}