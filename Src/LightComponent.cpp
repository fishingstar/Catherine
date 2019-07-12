#include <LightComponent.h>
#include <ISceneObject.h>
#include <ILevel.h>
#include <IWorld.h>
#include <LightManager.h>

namespace Catherine
{
	void LightComponent::OnAddComponent(ISceneObject * owner)
	{
		LightManager * tmp_manager = owner->GetLevel()->GetWorld()->GetLightManager();
		tmp_manager->Register(owner);
	}

	void LightComponent::OnRemoveComponent(ISceneObject * owner)
	{
		LightManager * tmp_manager = owner->GetLevel()->GetWorld()->GetLightManager();
		tmp_manager->Unregister(owner);
	}

	void LightComponent::Update(float deltaTime)
	{

	}

	ComponentKind LightComponent::GetComponentKind() const
	{
		return ComponentKind::Light;
	}
}