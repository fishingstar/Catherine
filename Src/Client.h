#pragma once

namespace Catherine
{
	class IDevice;
	class IWorld;
	class IRenderer;

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
		bool CreateWorld();
		bool CreateRenderer();

		void OnFrameBegin();
		void OnFrameEnd();

		void Update(float deltaTime);
		void UpdateLogic(float deltaTime);
		void UpdateRender(float deltaTime);

	private:
		IDevice * m_Device = nullptr;
		IWorld * m_World = nullptr;
		IRenderer * m_Renderer = nullptr;
	};
}