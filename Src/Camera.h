#pragma once

#include <ICamera.h>

namespace Catherine
{
	class Camera : public ICamera
	{
	public:
		virtual ProjectionMode GetProjectionMode();
		virtual void SetProjectionMode(ProjectionMode param_Mode);

		virtual float GetNearPlane() const;
		virtual void SetNearPlane(float param_Near);

		virtual float GetFarPlane() const;
		virtual void SetFarPlane(float param_Far);

		virtual float GetAspect() const;
		virtual void SetAspect(float param_Aspect);

		virtual float GetFOV() const;
		virtual void SetFOV(float param_FOV);

		virtual float GetSize() const;
		virtual void SetSize(float param_Size);

		virtual const glm::vec3 & GetClearColor() const;
		virtual void SetClearColor(const glm::vec3 & color);

		virtual const glm::vec3 & GetPosition() const;
		virtual void SetPosition(const glm::vec3 & pos);

		virtual const glm::vec3 & GetRotation() const;
		virtual void SetRotation(const glm::vec3 & rotation);

		virtual const glm::mat4x4 & GetViewMatrix();
		virtual const glm::mat4x4 & GetProjectionMatrix();

	private:
		void UpdateViewMatrix();
		void UpdateProjectionMatrix();

	private:
		ProjectionMode m_ProjectionMode = ProjectionMode::Persperctive;

		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.0f;
		float m_Aspect = 1.333f;
		float m_FieldofView = 45.0f;
		float m_Size = 5.0f;

		bool m_ViewDirty = true;
		glm::mat4x4 m_ViewMatrix;

		bool m_ProjectionDirty = true;
		glm::mat4x4 m_ProjectionMatrix;

		glm::vec3 m_ClearColor = glm::vec3(1.0, 1.0, 1.0);

		glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

		glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	};
}