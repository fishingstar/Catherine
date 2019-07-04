#include <GameWorld.h>
#include <Level.h>

namespace Catherine
{
	bool GameWorld::Initialize()
	{
		ILevel * tmp_level = new Level();
		tmp_level->Initialize();

		m_Levels.push_back(tmp_level);

		return true;
	}

	void GameWorld::Update(float deltaTime)
	{
		for (size_t i = 0; i < m_Levels.size(); i++)
		{
			m_Levels[i]->Update(deltaTime);
		}
	}
}