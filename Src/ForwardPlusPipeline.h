#pragma once

#include "IPipeline.h"

namespace Catherine
{
	class ForwardPlusPipeline : public IPipeline
	{
	public:
		virtual ~ForwardPlusPipeline() override { }

		virtual bool Initialize() override { }
		virtual void Uninitialize() override { }

		virtual void Render(const WorldContext * context) override { }
	};
}