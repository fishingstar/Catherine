#pragma once

namespace Catherine
{
	class IDevice;
	class IWorld;
	class WorldRenderer;

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
		void DeleteDevice();

		bool CreateWorld();
		void DeleteWorld();

		bool CreateRenderer();
		void DeleteRenderer();

		// TODO : delete frame begin and end
		void OnFrameBegin();
		void OnFrameEnd();

		void Update(float deltaTime);
		void UpdateLogic(float deltaTime);
		void UpdateRender(float deltaTime);

	private:
		// device interface
		IDevice * m_Device = nullptr;

		// editor world
		// EditorWorld * m_EditorWorld = nullptr;
		
		// game world
		IWorld * m_GameWorld = nullptr;

		// world renderer
		WorldRenderer * m_WorldRenderer = nullptr;
	};
}