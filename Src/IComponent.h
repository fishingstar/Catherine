#pragma once

#include <ComponentCommon.h>

namespace Catherine
{
	class ISceneObject;

	class IComponent
	{
	public:
		virtual void Update(float deltaTime) = 0;
		virtual ComponentKind GetComponentKind() const = 0;

	public:
		ISceneObject * GetOwner() const { return m_Owner; }
		void SetOwner(ISceneObject * owner) { m_Owner = owner; }

	private:
		ISceneObject * m_Owner = nullptr;
	};
}