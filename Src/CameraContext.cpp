#include "CameraContext.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Math3DUtility.h"

namespace Catherine
{
	void CameraContext::Apply()
	{
		CalculateViewMatrix();
		CalculateProjectionMatrix();
	}

	void CameraContext::CalculateViewMatrix()
	{
		m_ViewMatrix = Math3DUtility::GenViewMatrixFromRotation(m_Position, m_Rotation);
	}

	void CameraContext::CalculateProjectionMatrix()
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

	std::vector<glm::vec4> CameraContext::GetFrustumPoints(float near, float far) const
	{
		std::vector<glm::vec4> tmp_result;

		float near_x = 0.0f, near_y = 0.0f, near_z = 0.0f;
		float far_x = 0.0f, far_y = 0.0f, far_z = 0.0f;

		if (m_ProjectionMode == ProjectionMode::Persperctive)
		{
			near_x = glm::tan(glm::radians(m_FieldofView / 2.0f * m_Aspect)) * near;
			near_y = glm::tan(glm::radians(m_FieldofView / 2.0f)) * near;
			near_z = -near;
			far_x = glm::tan(glm::radians(m_FieldofView / 2.0f * m_Aspect)) * far;
			far_y = glm::tan(glm::radians(m_FieldofView / 2.0f)) * far;
			far_z = -far;
		}
		else
		{
			near_x = far_x = m_Size / 2.0f * m_Aspect;
			near_y = far_y = m_Size / 2.0f;
			near_z = -near;
			far_z = -far;
		}

		tmp_result.push_back(glm::vec4(near_x, near_y, near_z, 1.0f));
		tmp_result.push_back(glm::vec4(-near_x, near_y, near_z, 1.0f));
		tmp_result.push_back(glm::vec4(near_x, -near_y, near_z, 1.0f));
		tmp_result.push_back(glm::vec4(-near_x, -near_y, near_z, 1.0f));
		tmp_result.push_back(glm::vec4(far_x, far_y, far_z, 1.0f));
		tmp_result.push_back(glm::vec4(-far_x, far_y, far_z, 1.0f));
		tmp_result.push_back(glm::vec4(far_x, -far_y, far_z, 1.0f));
		tmp_result.push_back(glm::vec4(-far_x, -far_y, far_z, 1.0f));

		for (size_t i = 0; i < tmp_result.size(); ++i)
			tmp_result[i] = glm::inverse(m_ViewMatrix) * tmp_result[i];

		return tmp_result;
	}
}