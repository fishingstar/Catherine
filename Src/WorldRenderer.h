#pragma once

#include "IRenderer.h"
#include <vector>

namespace Catherine
{
	class IWorld;
	class IPipeline;

	class WorldRenderer : public IRenderer
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

	public:
		void RegisterWorld(IWorld * world);

	public:
		std::vector<IWorld *> m_Worlds;

		IPipeline * m_ForwardPipeline = nullptr;
		IPipeline * m_DeferredPipeline = nullptr;
		IPipeline * m_TileBasedDeferredPipeline = nullptr;
		IPipeline * m_ForwardPlusPipeline = nullptr;
	};
}
