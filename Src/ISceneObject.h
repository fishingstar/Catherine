#pragma once

#include <ComponentCommon.h>
#include <vector>

namespace Catherine
{
	class IComponent;

	class ISceneObject
	{
	public:
		virtual void Update(float deltaTime) = 0;

		virtual IComponent * GetComponent(ComponentKind kind) = 0;
		virtual const std::vector<IComponent *> & GetComponents(ComponentKind kind) = 0;

		virtual void AddComponent(IComponent * component) = 0;
		virtual void RemoveComponent(IComponent * component) = 0;
	};
}