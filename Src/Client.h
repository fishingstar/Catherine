#pragma once

#include <IDevice.h>

namespace Catherine
{
	class Client
	{
	public:
		static Client * Instance();

		bool Initialize();
		void Uninitialize();
		void Run();
		
	private:
		Client() { }

		bool CreateDevice();

		void OnFrameBegin();
		void OnFrameEnd();

		void Update(float deltaTime);
		void UpdateLogic(float deltaTime);
		void UpdateRender(float deltaTime);

	private:
		IDevice * m_Device = nullptr;
	};
}