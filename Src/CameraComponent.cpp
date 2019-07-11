#include <CameraComponent.h>

namespace Catherine
{
	void CameraComponent::OnAddComponent(ISceneObject * owner)
	{

	}

	void CameraComponent::OnRemoveComponent(ISceneObject * owner)
	{

	}

	void CameraComponent::Update(float deltaTime)
	{
		
	}

	ComponentKind CameraComponent::GetComponentKind() const
	{
		return ComponentKind::Camera;
	}
}