#include <GameWorld.h>
#include <Level.h>
#include <WorldContext.h>

namespace Catherine
{
	bool GameWorld::Initialize()
	{
		// create world context for rendering
		m_WorldContext = new WorldContext();

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

	void GameWorld::PreRender()
	{

	}

	void GameWorld::Render()
	{
		for (size_t i = 0; i < m_Levels.size(); i++)
		{
			m_Levels[i]->Render(m_WorldContext);
		}
	}

	void GameWorld::PostRender()
	{
		m_WorldContext->Clear();
	}
}