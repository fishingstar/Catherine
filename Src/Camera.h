#pragma once

#include <IComponent.h>
#include <CameraContext.h>

namespace Catherine
{
	class Camera : public IComponent
	{
	public:
		virtual void OnAddComponent(SceneObject * owner) override;
		virtual void OnRemoveComponent(SceneObject * owner) override;

		virtual void Update(float deltaTime) override;

		virtual ComponentKind GetComponentKind() const override;

	public:
		ProjectionMode GetProjectionMode() { return m_ProjectionMode; }
		void SetProjectionMode(ProjectionMode mode) { m_ProjectionMode = mode; }

		float GetNearPlane() const { return m_NearPlane; }
		void SetNearPlane(float value) { m_NearPlane = value; }

		float GetFarPlane() const { return m_FarPlane; }
		void SetFarPlane(float value) { m_FarPlane = value; }

		float GetAspect() const { return m_Aspect; }
		void SetAspect(float value) { m_Aspect = value; }

		float GetFOV() const { return m_FieldofView; }
		void SetFOV(float value) { m_FieldofView = value; }

		float GetSize() const { return m_Size; }
		void SetSize(float value) { m_Size = value; }

		const glm::vec3 & GetClearColor() const { return m_ClearColor; }
		void SetClearColor(const glm::vec3 & color) { m_ClearColor = color; }

	private:
		ProjectionMode m_ProjectionMode = ProjectionMode::Persperctive;

		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		float m_Aspect = 1.778f;
		float m_FieldofView = 45.0f;
		float m_Size = 5.0f;

		glm::vec3 m_ClearColor = glm::vec3(1.0, 1.0, 1.0);
	};
}