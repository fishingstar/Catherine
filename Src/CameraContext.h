#pragma once

#include "glm/glm.hpp"

namespace Catherine
{
	enum class ProjectionMode
	{
		Ortho,
		Persperctive
	};

	class CameraContext
	{
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

		const glm::vec3 & GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3 & position) { m_Position = position; }

		const glm::vec3 & GetRotation() const { return m_Rotation; }
		void SetRotation(const glm::vec3 & rotation) { m_Rotation = rotation; }

		const glm::mat4x4 & GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4x4 & GetProjectionMatrix() const { return m_ProjectionMatrix; }

		void Apply();

	private:
		void CalculateViewMatrix();
		void CalculateProjectionMatrix();

	private:
		ProjectionMode m_ProjectionMode = ProjectionMode::Persperctive;

		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		float m_Aspect = 1.333f;
		float m_FieldofView = 45.0f;
		float m_Size = 5.0f;

		glm::vec3 m_ClearColor = glm::vec3(1.0f, 1.0f, 1.0f);

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::mat4x4 m_ViewMatrix;
		glm::mat4x4 m_ProjectionMatrix;
	};
}