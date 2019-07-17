#include "Light.h"
#include "SceneObject.h"
#include "ILevel.h"
#include "IWorld.h"
#include "LightManager.h"

namespace Catherine
{
	void Light::OnAddComponent(SceneObject * owner)
	{
		LightManager * tmp_manager = owner->GetLevel()->GetWorld()->GetLightManager();
		tmp_manager->Register(owner);
	}

	void Light::OnRemoveComponent(SceneObject * owner)
	{
		LightManager * tmp_manager = owner->GetLevel()->GetWorld()->GetLightManager();
		tmp_manager->Unregister(owner);
	}

	void Light::Update(float deltaTime)
	{

	}

	ComponentKind Light::GetComponentKind() const
	{
		return ComponentKind::Light;
	}
}