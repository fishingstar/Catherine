#pragma once

#include <ILevel.h>
#include <vector>

namespace Catherine
{
	class ISceneObject;

	class Level : public ILevel
	{
	public:
		Level(IWorld * world) : ILevel(world) { }

		virtual void Initialize() override;
		virtual void Update(float deltaTime) override;
		virtual void Render(WorldContext * context) override;

	private:
		std::vector<ISceneObject *> m_SceneObjects;
	};
}