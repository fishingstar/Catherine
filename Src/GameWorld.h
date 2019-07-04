#pragma once

#include <IWorld.h>
#include <vector>

namespace Catherine
{
	class ILevel;

	class GameWorld : public IWorld
	{
	public:
		virtual bool Initialize() override;
		virtual void Update(float deltaTime) override;

	private:
		std::vector<ILevel *> m_Levels;
	};
}