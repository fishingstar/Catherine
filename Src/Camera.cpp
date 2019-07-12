#include <Camera.h>
#include <CameraManager.h>
#include <ISceneObject.h>
#include <ILevel.h>
#include <IWorld.h>

namespace Catherine
{
	void Camera::OnAddComponent(ISceneObject * owner)
	{
		CameraManager * tmp_manager = owner->GetLevel()->GetWorld()->GetCameraManager();
		tmp_manager->Register(owner);
	}

	void Camera::OnRemoveComponent(ISceneObject * owner)
	{
		CameraManager * tmp_manager = owner->GetLevel()->GetWorld()->GetCameraManager();
		tmp_manager->Unregister(owner);
	}

	void Camera::Update(float deltaTime)
	{
		
	}

	ComponentKind Camera::GetComponentKind() const
	{
		return ComponentKind::Camera;
	}
}