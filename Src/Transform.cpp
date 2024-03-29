#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Catherine
{
	void Transform::OnAddComponent(SceneObject * owner)
	{

	}

	void Transform::OnRemoveComponent(SceneObject * owner)
	{

	}

	void Transform::Update(float deltaTime)
	{
		// logic
	}

	ComponentKind Transform::GetComponentKind() const
	{
		return ComponentKind::Transform;
	}

	Transform * Transform::GetParent() const
	{
		return m_Parent;
	}

	Transform * Transform::GetChild(unsigned int index) const
	{
		return index < m_Children.size() ? m_Children[index] : nullptr;
	}

	unsigned int Transform::GetChildCount() const
	{
		return (unsigned int)m_Children.size();
	}

	const glm::vec3 & Transform::GetPosition() const
	{
		return m_Position;
	}

	void Transform::SetPosition(const glm::vec3 & position)
	{
		if (position != m_Position)
		{
			m_Position = position;
			m_WorldMatrixDirty = true;
		}
	}

	const glm::vec3 & Transform::GetRotation() const
	{
		return m_Rotation;
	}

	void Transform::SetRotation(const glm::vec3 & rotation)
	{
		if (rotation != m_Rotation)
		{
			m_Rotation = rotation;
			m_WorldMatrixDirty = true;
		}
	}

	const glm::vec3 & Transform::GetScale() const
	{
		return m_Scale;
	}

	void Transform::SetScale(const glm::vec3 & scale)
	{
		if (scale != m_Scale)
		{
			m_Scale = scale;
			m_WorldMatrixDirty = true;
		}
	}
}