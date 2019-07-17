#include "Client.h"
#include "LogUtility.h"
#include "DeviceFactory.h"
#include "WorldFactory.h"
#include "RendererFactory.h"
#include "WorldRenderer.h"
#include "IWorld.h"

namespace Catherine
{
	extern IDevice * g_Device;

	Client * Client::Instance()
	{
		static Client s_instance;
		return &s_instance;
	}

	bool Client::Initialize()
	{
		// low level API
		bool tmp_deviceOK = CreateDevice();
		if (!tmp_deviceOK)
		{
			LogError("Client CreateDevice Failed...");
			return false;
		}

		// logic world
		bool tmp_worldOK = CreateWorld();
		if (!tmp_worldOK)
		{
			LogError("Client CreateWorld Failed...");
			return false;
		}

		// render world
		bool tmp_renderOK = CreateRenderer();
		if (!tmp_renderOK)
		{
			LogError("Client CreateRenderer Failed...");
			return false;
		}

		// register world to renderer
		m_WorldRenderer->RegisterWorld(m_GameWorld);
		// m_WorldRenderer->RegisterWorld(m_EditorWorld);

		return true;
	}

	void Client::Uninitialize()
	{
		// other uninitialize
		// ...

		DeleteRenderer();
		DeleteWorld();
		DeleteDevice();
	}

	void Client::Run()
	{
		while (!m_Device->Close())
		{
			OnFrameBegin();

			// TODO : fill delta Time
			Update(0.0f);

			OnFrameEnd();
		}
	}

	void Client::OnFrameBegin()
	{
		m_Device->OnFrameBegin();
	}

	void Client::OnFrameEnd()
	{
		m_Device->OnFrameEnd();
	}

	void Client::Update(float deltaTime)
	{
		// TODO : seperate logic and render update rate

		// update gameplay logic
		UpdateLogic(deltaTime);
		// render display
		UpdateRender(deltaTime);
	}

	void Client::UpdateLogic(float deltaTime)
	{
		// before update
		m_GameWorld->PreUpdate(deltaTime);
		// update
		m_GameWorld->Update(deltaTime);
		// after update
		m_GameWorld->PostUpdate(deltaTime);
	}

	void Client::UpdateRender(float deltaTime)
	{
		// before render
		m_WorldRenderer->PreRender();
		// render
		m_WorldRenderer->Render();
		// after render
		m_WorldRenderer->PostRender();
	}

	bool Client::CreateDevice()
	{
		m_Device = DeviceFactory::Instance()->CreateDevice();
		if (m_Device == nullptr)
		{
			LogError("Create Device Failed...");
			return false;
		}

		bool tmp_initialized = m_Device->Initialize();
		if (!tmp_initialized)
		{
			LogError("Device Initialize Failed...");
			DeviceFactory::Instance()->DeleteDevice(m_Device);
			m_Device = nullptr;
			return false;
		}

		g_Device = m_Device;
		return true;
	}

	void Client::DeleteDevice()
	{
		if (m_Device)
		{
			g_Device = nullptr;

			m_Device->Uninitialize();

			DeviceFactory::Instance()->DeleteDevice(m_Device);
			m_Device = nullptr;
		}
	}

	bool Client::CreateWorld()
	{
		m_GameWorld = WorldFactory::Instance()->CreateGameWorld();
		if (m_GameWorld == nullptr)
		{
			LogError("Create World Failed...");
			return false;
		}

		bool tmp_initialized = m_GameWorld->Initialize();
		if (!tmp_initialized)
		{
			LogError("World Initialize Failed...");
			WorldFactory::Instance()->DeleteWorld(m_GameWorld);
			m_GameWorld = nullptr;
			return false;
		}

		return true;
	}

	void Client::DeleteWorld()
	{
		if (m_GameWorld)
		{
			m_GameWorld->Uninitialize();

			WorldFactory::Instance()->DeleteWorld(m_GameWorld);
			m_GameWorld = nullptr;
		}
	}

	bool Client::CreateRenderer()
	{
		m_WorldRenderer = RendererFactory::Instance()->CreateWorldRenderer();
		if (m_WorldRenderer == nullptr)
		{
			LogError("Create Render Failed...");
			return false;
		}

		bool tmp_initialized = m_WorldRenderer->Initialize();
		if (!tmp_initialized)
		{
			LogError("Renderer Initialize Failed...");
			RendererFactory::Instance()->DeleteRenderer(m_WorldRenderer);
			m_WorldRenderer = nullptr;
			return false;
		}

		return true;
	}

	void Client::DeleteRenderer()
	{
		if (m_WorldRenderer)
		{
			m_WorldRenderer->Uninitialize();

			RendererFactory::Instance()->DeleteRenderer(m_WorldRenderer);
			m_WorldRenderer = nullptr;
		}
	}
}