#pragma once

#include "IPipeline.h"

namespace Catherine
{
	class ForwardPipeline : public IPipeline
	{
	public:
		virtual ~ForwardPipeline() override { }

		virtual bool Initialize() override { return true; }
		virtual void Uninitialize() override { }

		virtual void Render(const WorldContext * context) override;

	private:
		void RenderShadow(const WorldContext * context);
		void RenderOpaque(const WorldContext * context);
		void RenderTransparent(const WorldContext * context);
	};
}