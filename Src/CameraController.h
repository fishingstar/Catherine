#pragma once

#include "IComponent.h"

namespace Catherine
{
	class CameraController : public IComponent
	{
	public:
		virtual void OnAddComponent(SceneObject * owner) override;
		virtual void OnRemoveComponent(SceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;

	private:

	};
}