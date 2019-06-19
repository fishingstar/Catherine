#include <Client.h>
#include <DeviceFactory.h>
#include <global.h>
#include <log.h>

namespace Catherine
{
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
			LogModule::Instance()->LogError("Client CreateDevice Failed...");
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

	}

	void Client::UpdateRender(float deltaTime)
	{

	}

	bool Client::CreateDevice()
	{
		m_Device = DeviceFactory::Instance()->CreateDevice();
		if (m_Device == nullptr)
		{
			LogModule::Instance()->LogError("Create Device Failed...");
			return false;
		}

		bool tmp_initialized = m_Device->Initialize();
		if (!tmp_initialized)
		{
			LogModule::Instance()->LogError("Device Initialize Failed...");
			m_Device = nullptr;
			return false;
		}

		g_Device = m_Device;
		return true;
	}
}