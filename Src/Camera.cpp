#include <Camera.h>

#include <glm/gtc/matrix_transform.hpp>

namespace Catherine
{
	ProjectionMode Camera::GetProjectionMode()
	{
		return m_ProjectionMode;
	}

	void Camera::SetProjectionMode(ProjectionMode param_Mode)
	{
		if (m_ProjectionMode != param_Mode)
		{
			m_ProjectionMode = param_Mode;
			m_ProjectionDirty = true;
		}
	}

	float Camera::GetNearPlane() const
	{
		return m_NearPlane;
	}

	void Camera::SetNearPlane(float param_Near)
	{
		if (m_NearPlane != param_Near)
		{
			m_NearPlane = param_Near;
			m_ProjectionDirty = true;
		}
	}

	float Camera::GetFarPlane() const
	{
		return m_FarPlane;
	}

	void Camera::SetFarPlane(float param_Far)
	{
		if (m_FarPlane != param_Far)
		{
			m_FarPlane = param_Far;
			m_ProjectionDirty = true;
		}
	}

	float Camera::GetAspect() const
	{
		return m_Aspect;
	}

	void Camera::SetAspect(float param_Aspect)
	{
		if (m_Aspect != param_Aspect)
		{
			m_Aspect = param_Aspect;
			m_ProjectionDirty = true;
		}
	}

	float Camera::GetFOV() const
	{
		return m_FieldofView;
	}

	void Camera::SetFOV(float param_FOV)
	{
		if (m_FieldofView != param_FOV)
		{
			m_FieldofView = param_FOV;
			m_ProjectionDirty = true;
		}
	}

	float Camera::GetSize() const
	{
		return m_Size;
	}

	void Camera::SetSize(float param_Size)
	{
		if (m_Size != param_Size)
		{
			m_Size = param_Size;
			m_ProjectionDirty = true;
		}
	}

	const glm::vec3 & Camera::GetClearColor() const
	{
		return m_ClearColor;
	}

	void Camera::SetClearColor(const glm::vec3 & color)
	{
		m_ClearColor = color;
	}

	void Camera::SetPosition(float x, float y, float z)
	{
		glm::vec3 tmp_vector = glm::vec3(x, y, z);
		if (tmp_vector != m_Position)
		{
			m_Position = tmp_vector;
			m_ViewDirty = true;
		}
	}

	void Camera::SetRotate(float x, float y, float z)
	{
		glm::vec3 tmp_vector = glm::vec3(x, y, z);
		if (tmp_vector != m_Rotate)
		{
			m_Rotate = tmp_vector;
			m_ViewDirty = true;
		}
	}

	const glm::mat4x4 & Camera::GetViewMatrix()
	{
		if (m_ViewDirty)
		{
			UpdateViewMatrix();
		}

		return m_ViewMatrix;
	}

	const glm::mat4x4 & Camera::GetProjectionMatrix()
	{
		if (m_ProjectionDirty)
		{
			UpdateProjectionMatrix();
		}

		return m_ProjectionMatrix;
	}

	void Camera::UpdateViewMatrix()
	{
		glm::mat4x4 tmp_rotate = glm::mat4x4(1);
		tmp_rotate = glm::rotate(tmp_rotate, glm::radians(m_Rotate.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		tmp_rotate = glm::rotate(tmp_rotate, glm::radians(m_Rotate.y), glm::vec3(0.0f, -1.0f, 0.0f));
		m_Forward = tmp_rotate * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);

		glm::vec3 tmp_right = glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 tmp_up = glm::cross(tmp_right, m_Forward);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Forward, tmp_up);
	}

	void Camera::UpdateProjectionMatrix()
	{
		if (m_ProjectionMode == ProjectionMode::Persperctive)
		{
			m_ProjectionMatrix = glm::perspective(m_FieldofView, m_Aspect, m_NearPlane, m_FarPlane);
		}
		else
		{
			m_ProjectionMatrix = glm::ortho(-m_Size * m_Aspect / 2.0f, m_Size * m_Aspect / 2.0f, -m_Size / 2.0f, m_Size / 2.0f, m_NearPlane, m_FarPlane);
		}
	}
}