#pragma once

#include <IComponent.h>

namespace Catherine
{
	class CameraComponent : public IComponent
	{
	public:
		virtual void OnAddComponent(ISceneObject * owner) override;
		virtual void OnRemoveComponent(ISceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;
	};
}