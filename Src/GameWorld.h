#pragma once

#include <IWorld.h>

namespace Catherine
{
	class GameWorld : public IWorld
	{
	public:
		virtual void Update(float deltaTime) override;
	};
}