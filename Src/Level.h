#pragma once

#include "ILevel.h"
#include <vector>

namespace Catherine
{
	class SceneObject;

	class Level : public ILevel
	{
	public:
		Level(IWorld * world) : ILevel(world) { }

		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void Update(float deltaTime) override;
		virtual void Render(WorldContext * context) override;

	private:
		std::vector<SceneObject *> m_SceneObjects;
	};
}