#pragma once

#include "IRenderer.h"
#include <vector>

namespace Catherine
{
	class IWorld;

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
	};
}
