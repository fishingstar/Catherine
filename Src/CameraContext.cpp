#include "CameraContext.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Catherine
{
	const glm::mat4x4 & CameraContext::GetViewMatrix() const
	{
		glm::mat4x4 tmp_rotate = glm::mat4x4(1);
		tmp_rotate = glm::rotate(tmp_rotate, glm::radians(m_Rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		tmp_rotate = glm::rotate(tmp_rotate, glm::radians(m_Rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
		tmp_rotate = glm::rotate(tmp_rotate, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));

		glm::vec3 tmp_forward = tmp_rotate * glm::vec4(0.0f, 0.0f, -1.0f, 0.0f);
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