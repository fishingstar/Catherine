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
}