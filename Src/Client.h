#pragma once

namespace Catherine
{
	class IDevice;
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
		bool CreateRenderer();

		void OnFrameBegin();
		void OnFrameEnd();

		void Update(float deltaTime);
		void UpdateLogic(float deltaTime);
		void UpdateRender(float deltaTime);

	private:
		IDevice * m_Device = nullptr;
		IRenderer * m_Renderer = nullptr;
	};
}