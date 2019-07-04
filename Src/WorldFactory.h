#pragma once

namespace Catherine
{
	class IWorld;

	class WorldFactory
	{
	public:
		static WorldFactory * Instance();

		IWorld * CreateGameWorld();
		void DeleteWorld(IWorld * world);

	private:
		WorldFactory() { }
	};
}