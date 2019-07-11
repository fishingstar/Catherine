#include <SceneObject.h>

#include <IComponent.h>
#include <algorithm>

namespace Catherine
{
	void SceneObject::Update(float deltaTime)
	{

	}

	void SceneObject::Render(WorldContext * context)
	{

	}

	IComponent * SceneObject::GetComponent(ComponentKind kind)
	{
		IComponent * tmp_result = nullptr;

		const std::vector<IComponent *> & tmp_components = m_Components[kind];
		if (tmp_components.size() > 0)
			tmp_result = tmp_components[0];

		return tmp_result;
	}

	const std::vector<IComponent *> & SceneObject::GetComponents(ComponentKind kind)
	{
		return m_Components[kind];
	}

	void SceneObject::AddComponent(IComponent * component)
	{
		if (component != nullptr)
		{
			std::vector<IComponent *> & tmp_components = m_Components[component->GetComponentKind()];
			auto tmp_iter = std::find(tmp_components.begin(), tmp_components.end(), component);
			if (tmp_iter == tmp_components.end())
			{
				tmp_components.push_back(component);
				component->SetOwner(this);
				component->OnAddComponent(this);
			}
		}
	}

	void SceneObject::RemoveComponent(IComponent * component)
	{
		if (component != nullptr)
		{
			std::vector<IComponent *> & tmp_components = m_Components[component->GetComponentKind()];
			auto tmp_iter = std::find(tmp_components.begin(), tmp_components.end(), component);
			if (tmp_iter != tmp_components.end())
			{
				tmp_components.erase(tmp_iter);
				component->SetOwner(nullptr);
				component->OnRemoveComponent(this);
			}
		}
	}
}