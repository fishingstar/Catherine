#include <Client.h>
#include <DeviceFactory.h>
#include <WorldFactory.h>
#include <RendererFactory.h>
#include <IRenderer.h>
#include <LogUtility.h>
#include <global.h>
#include <GameWorld.h>

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
		bool tmp_deviceOK = CreateDevice();
		if (!tmp_deviceOK)
		{
			LogError("Client CreateDevice Failed...");
			return false;
		}

		bool tmp_worldOK = CreateWorld();
		if (!tmp_worldOK)
		{
			LogError("Client CreateWorld Failed...");
			return false;
		}

		bool tmp_renderOK = CreateRenderer();
		if (!tmp_renderOK)
		{
			LogError("Client CreateRenderer Failed...");
			return false;
		}

		// other initialize
		// ...

		return true;
	}

	void Client::Uninitialize()
	{
		// other uninitialize
		// ...

		m_Renderer->Uninitialize();
		m_Device->Uninitialize();
	}

	void Client::Run()
	{
		while (!m_Device->WindowShouldClose())
		{
			OnFrameBegin();

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
		// update gameplay logic
		UpdateLogic(deltaTime);
		// update render context
		UpdateRender(deltaTime);
	}

	void Client::UpdateLogic(float deltaTime)
	{
		m_World->Update(deltaTime);
	}

	void Client::UpdateRender(float deltaTime)
	{
		// before render
		m_Renderer->PreRender();
		// render
		m_Renderer->Render();
		// after render
		m_Renderer->PostRender();
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

	bool Client::CreateWorld()
	{
		m_World = WorldFactory::Instance()->CreateGameWorld();
		if (m_World == nullptr)
		{
			LogError("Create World Failed...");
			return false;
		}

		bool tmp_initialized = m_World->Initialize();
		if (!tmp_initialized)
		{
			LogError("World Initialize Failed...");
			WorldFactory::Instance()->DeleteWorld(m_World);
			m_World = nullptr;
			return false;
		}

		return true;
	}

	bool Client::CreateRenderer()
	{
		m_Renderer = RendererFactory::Instance()->CreateWorldRenderer();
		if (m_Renderer == nullptr)
		{
			LogError("Create Render Failed...");
			return false;
		}

		bool tmp_initialized = m_Renderer->Initialize();
		if (!tmp_initialized)
		{
			LogError("Renderer Initialize Failed...");
			RendererFactory::Instance()->DeleteRenderer(m_Renderer);
			m_Renderer = nullptr;
			return false;
		}

		return true;
	}
}