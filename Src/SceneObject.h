#pragma once

#include <ComponentCommon.h>
#include <unordered_map>
#include <vector>

namespace Catherine
{
	class IComponent;
	class WorldContext;
	class ILevel;

	class SceneObject
	{
	public:
		SceneObject(ILevel * level) : m_Level(level) { }

		bool Initialize();
		void Uninitialize();

		void Update(float deltaTime);
		void Render(WorldContext * context);

		void AddComponent(IComponent * component);
		void RemoveComponent(IComponent * component);
		IComponent * GetComponent(ComponentKind kind);
		const std::vector<IComponent *> & GetComponents(ComponentKind kind);

		ILevel * GetLevel() const { return m_Level; }

	private:
		std::unordered_map<ComponentKind, std::vector<IComponent *>> m_Components;

		ILevel * m_Level;
	};
}