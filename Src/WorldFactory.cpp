#include "WorldFactory.h"
#include "GameWorld.h"

namespace Catherine
{
	WorldFactory * WorldFactory::Instance()
	{
		static WorldFactory s_instance;
		return &s_instance;
	}

	IWorld * WorldFactory::CreateGameWorld()
	{
		IWorld * tmp_world = new GameWorld();
		return tmp_world;
	}

	void WorldFactory::DeleteWorld(IWorld * world)
	{
		if (world != nullptr)
		{
			delete world;
		}
	}
}