#pragma once

#include <IComponent.h>
#include <glm/glm.hpp>
#include <vector>

namespace Catherine
{
	class TransformComponent : public IComponent
	{
	public:
		virtual void Update(float deltaTime) override;

		virtual ISceneObject * GetOwner() const override;
		virtual void SetOwner(ISceneObject * owner) override;

		virtual ComponentKind GetComponentKind() const override;

	public:
		TransformComponent * GetParent() const;
		TransformComponent * GetChild(unsigned int index) const;
		unsigned int GetChildCount() const;

		const glm::vec3 & GetPosition() const;
		void SetPosition(const glm::vec3 & position);

		const glm::vec3 & GetRotation() const;
		void SetRotation(const glm::vec3 & rotation);

		const glm::vec3 & GetScale() const;
		void SetScale(const glm::vec3 & scale);

		const glm::mat4 & GetWorldMatrix();

	private:
		ISceneObject * m_Owner = nullptr;

		TransformComponent * m_Parent = nullptr;
		std::vector<TransformComponent *> m_Children;

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0, 1.0f, 1.0f);

		glm::mat4 m_WorldMatrix = glm::mat4(1.0f);
		bool m_WorldMatrixDirty = true;
	};
}