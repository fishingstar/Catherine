#include <GameWorld.h>
#include <Level.h>
#include <WorldContext.h>
#include <CameraManager.h>
#include <LightManager.h>

namespace Catherine
{
	bool GameWorld::Initialize()
	{
		// create world context for rendering
		m_WorldContext = new WorldContext();
		// create camera manager for this world
		m_CameraManager = new CameraManager();
		// create light manager for this world
		m_LightManager = new LightManager();

		ILevel * tmp_level = new Level(this);
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
		CameraContext * tmp_camera = m_CameraManager->GetCameraContext();
		m_WorldContext->SetCameraContext(tmp_camera);

		LightContext * tmp_light = m_LightManager->GetLightContext();
		m_WorldContext->SetLightContext(tmp_light);

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