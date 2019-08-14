#include "CameraContext.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Math3DUtility.h"

namespace Catherine
{
	const glm::mat4x4 & CameraContext::GetViewMatrix() const
	{
		glm::vec3 tmp_forward = Math3DUtility::RotationDirection(m_Rotation, glm::vec3(0.0f, 0.0f, -1.0f));
		glm::vec3 tmp_right = glm::cross(tmp_forward, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 tmp_up = glm::cross(tmp_right, tmp_forward);
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + tmp_forward, tmp_up);

		return m_ViewMatrix;
	}

	const glm::mat4x4 & CameraContext::GetProjectionMatrix() const
	{
		if (m_ProjectionMode == ProjectionMode::Persperctive)
		{
			m_ProjectionMatrix = glm::perspective(m_FieldofView, m_Aspect, m_NearPlane, m_FarPlane);
		}
		else
		{
			m_ProjectionMatrix = glm::ortho(-m_Size * m_Aspect / 2.0f, m_Size * m_Aspect / 2.0f, -m_Size / 2.0f, m_Size / 2.0f, m_NearPlane, m_FarPlane);
		}

		return m_ProjectionMatrix;
	}
}