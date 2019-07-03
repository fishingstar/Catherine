#include <TransformComponent.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Catherine
{
	void TransformComponent::Initialize(ISceneObject * owner)
	{
		m_Owner = owner;
	}

	void TransformComponent::Update(float deltaTime)
	{
		// logic
	}

	ComponentKind TransformComponent::GetComponentKind() const
	{
		return ComponentKind::Transform;
	}

	ISceneObject * TransformComponent::GetOwner() const
	{
		return m_Owner;
	}

	TransformComponent * TransformComponent::GetParent() const
	{
		return m_Parent;
	}

	TransformComponent * TransformComponent::GetChild(unsigned int index) const
	{
		return index < m_Children.size() ? m_Children[index] : nullptr;
	}

	unsigned int TransformComponent::GetChildCount() const
	{
		return (unsigned int)m_Children.size();
	}

	const glm::vec3 & TransformComponent::GetPosition() const
	{
		return m_Position;
	}

	void TransformComponent::SetPosition(const glm::vec3 & position)
	{
		if (position != m_Position)
		{
			m_Position = position;
			m_WorldMatrixDirty = true;
		}
	}

	const glm::vec3 & TransformComponent::GetRotation() const
	{
		return m_Rotation;
	}

	void TransformComponent::SetRotation(const glm::vec3 & rotation)
	{
		if (rotation != m_Rotation)
		{
			m_Rotation = rotation;
			m_WorldMatrixDirty = true;
		}
	}

	const glm::vec3 & TransformComponent::GetScale() const
	{
		return m_Scale;
	}

	void TransformComponent::SetScale(const glm::vec3 & scale)
	{
		if (scale != m_Scale)
		{
			m_Scale = scale;
			m_WorldMatrixDirty = true;
		}
	}

	const glm::mat4 & TransformComponent::GetWorldMatrix()
	{
		if (m_WorldMatrixDirty)
		{
			m_WorldMatrix = glm::mat4(1.0f);
			m_WorldMatrix = glm::scale(m_WorldMatrix, m_Scale);
			m_WorldMatrix = glm::rotate(m_WorldMatrix, glm::radians(m_Rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
			m_WorldMatrix = glm::rotate(m_WorldMatrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
			m_WorldMatrix = glm::rotate(m_WorldMatrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
			m_WorldMatrix = glm::translate(m_WorldMatrix, m_Position);
		}
		return m_WorldMatrix;
	}
}