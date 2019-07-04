#pragma once

#include <ILevel.h>
#include <vector>

namespace Catherine
{
	class ISceneObject;

	class Level : public ILevel
	{
	public:
		virtual void Initialize() override;
		virtual void Update(float deltaTime) override;

	private:
		std::vector<ISceneObject *> m_SceneObjects;
	};
}