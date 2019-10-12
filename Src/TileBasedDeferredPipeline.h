#pragma once

#include "IPipeline.h"

namespace Catherine
{
	class IProgram;

	class TileBasedDeferredPipeline : public IPipeline
	{
	public:
		virtual ~TileBasedDeferredPipeline() override;

		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void Render(const WorldContext * context) override;

	private:
		void RenderGeometry(const WorldContext * context);
		void ComputeLight(const WorldContext * context);
		void RenderLighting(const WorldContext * context);

	private:
		IProgram * m_ComputeProgram = nullptr;
	};
}