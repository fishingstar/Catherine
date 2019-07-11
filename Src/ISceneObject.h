#pragma once

#include <ComponentCommon.h>
#include <vector>

namespace Catherine
{
	class IComponent;
	class WorldContext;
	class ILevel;

	class ISceneObject
	{
	public:
		ISceneObject(ILevel * level) : m_Level(level) { }

		virtual void Update(float deltaTime) = 0;
		virtual void Render(WorldContext * context) = 0;

		virtual IComponent * GetComponent(ComponentKind kind) = 0;
		virtual const std::vector<IComponent *> & GetComponents(ComponentKind kind) = 0;

		virtual void AddComponent(IComponent * component) = 0;
		virtual void RemoveComponent(IComponent * component) = 0;

	public:
		ILevel * GetLevel() const { return m_Level; }

	private:
		ILevel * m_Level;
	};
}