#pragma once

#include <ComponentCommon.h>

namespace Catherine
{
	class ISceneObject;

	class IComponent
	{
	public:
		virtual void Update(float deltaTime) = 0;
		
		virtual ISceneObject * GetOwner() const = 0;
		virtual void SetOwner(ISceneObject * owner) = 0;

		virtual ComponentKind GetComponentKind() const = 0;
	};
}