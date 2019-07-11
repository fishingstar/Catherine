#include <LightComponent.h>

namespace Catherine
{
	void LightComponent::OnAddComponent(ISceneObject * owner)
	{

	}

	void LightComponent::OnRemoveComponent(ISceneObject * owner)
	{

	}

	void LightComponent::Update(float deltaTime)
	{

	}

	ComponentKind LightComponent::GetComponentKind() const
	{
		return ComponentKind::Light;
	}
}