#pragma once

#include <ComponentCommon.h>

namespace Catherine
{
	class SceneObject;

	class IComponent
	{
	public:
		virtual void OnAddComponent(SceneObject * owner) = 0;
		virtual void OnRemoveComponent(SceneObject * owner) = 0;

		virtual void Update(float deltaTime) = 0;

		virtual ComponentKind GetComponentKind() const = 0;

	public:
		SceneObject * GetOwner() const { return m_Owner; }
		void SetOwner(SceneObject * owner) { m_Owner = owner; }

	private:
		SceneObject * m_Owner = nullptr;
	};
}