#include <CameraComponent.h>
#include <CameraManager.h>
#include <ISceneObject.h>
#include <ILevel.h>
#include <IWorld.h>

namespace Catherine
{
	void CameraComponent::OnAddComponent(ISceneObject * owner)
	{
		CameraManager * tmp_manager = owner->GetLevel()->GetWorld()->GetCameraManager();
		tmp_manager->Register(owner);
	}

	void CameraComponent::OnRemoveComponent(ISceneObject * owner)
	{
		CameraManager * tmp_manager = owner->GetLevel()->GetWorld()->GetCameraManager();
		tmp_manager->Unregister(owner);
	}

	void CameraComponent::Update(float deltaTime)
	{
		
	}

	ComponentKind CameraComponent::GetComponentKind() const
	{
		return ComponentKind::Camera;
	}
}