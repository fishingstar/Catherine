#pragma once

#include <IComponent.h>
#include <glm/glm.hpp>
#include <vector>

namespace Catherine
{
	class Transform : public IComponent
	{
	public:
		virtual void OnAddComponent(SceneObject * owner) override;
		virtual void OnRemoveComponent(SceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;

	public:
		Transform * GetParent() const;
		Transform * GetChild(unsigned int index) const;
		unsigned int GetChildCount() const;

		const glm::vec3 & GetPosition() const;
		void SetPosition(const glm::vec3 & position);

		const glm::vec3 & GetRotation() const;
		void SetRotation(const glm::vec3 & rotation);

		const glm::vec3 & GetScale() const;
		void SetScale(const glm::vec3 & scale);

		const glm::mat4 & GetWorldMatrix();

	private:
		Transform * m_Parent = nullptr;
		std::vector<Transform *> m_Children;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0, 1.0f, 1.0f);

		glm::mat4 m_WorldMatrix = glm::mat4(1.0f);
		bool m_WorldMatrixDirty = true;
	};
}