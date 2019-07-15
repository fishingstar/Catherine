#pragma once

namespace Catherine
{
	class WorldContext;
	class IWorld;

	class ILevel
	{
	public:
		ILevel(IWorld * world) : m_World(world) { }

		virtual bool Initialize() = 0;
		virtual void Uninitialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(WorldContext * context) = 0;

	public:
		IWorld * GetWorld() const { return m_World; }

	private:
		IWorld * m_World;
	};
}