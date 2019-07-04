#pragma once

#include <ISceneObject.h>
#include <unordered_map>

namespace Catherine
{
	class SceneObject : public ISceneObject
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render(WorldContext * context) override;

		virtual IComponent * GetComponent(ComponentKind kind) override;
		virtual const std::vector<IComponent *> & GetComponents(ComponentKind kind) override;

		virtual void AddComponent(IComponent * component) override;
		virtual void RemoveComponent(IComponent * component) override;

	private:
		std::unordered_map<ComponentKind, std::vector<IComponent *>> m_Components;
	};
}