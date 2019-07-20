#include "GameWorld.h"
#include "Level.h"
#include "WorldContext.h"
#include "CameraManager.h"
#include "LightManager.h"
#include "Skybox.h"

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

		// TODO : delete test level
		ILevel * tmp_testLevel = new Level(this);
		bool tmp_levelOK = tmp_testLevel->Initialize();
		if (tmp_levelOK)
		{
			m_Levels.push_back(tmp_testLevel);
		}

		m_Skybox = new Skybox();
		m_Skybox->Initialize();

		return true;
	}

	void GameWorld::Uninitialize()
	{
		m_Skybox->Uninitialize();

		for (size_t i = 0; i < m_Levels.size(); i++)
		{
			if (m_Levels[i])
			{
				m_Levels[i]->Uninitialize();

				delete m_Levels[i];
				m_Levels[i] = nullptr;
			}
		}
		m_Levels.clear();

		if (m_LightManager)
		{
			delete m_LightManager;
			m_LightManager = nullptr;
		}

		if (m_CameraManager)
		{
			delete m_CameraManager;
			m_CameraManager = nullptr;
		}

		if (m_WorldContext)
		{
			delete m_WorldContext;
			m_WorldContext = nullptr;
		}
	}

	void GameWorld::PreUpdate(float deltaTime)
	{

	}

	void GameWorld::Update(float deltaTime)
	{
		for (size_t i = 0; i < m_Levels.size(); i++)
		{
			m_Levels[i]->Update(deltaTime);
		}
	}

	void GameWorld::PostUpdate(float deltaTime)
	{

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

		m_Skybox->Render(m_WorldContext);
	}

	void GameWorld::PostRender()
	{
		m_WorldContext->Clear();
	}
}