#include "RenderContext.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Catherine
{
	void RenderContext::Apply()
	{
		m_ModelMatrix = glm::mat4x4(1.0f);
		// 3rd position
		m_ModelMatrix = glm::translate(m_ModelMatrix, m_Position);
		
		// 2nd rotation
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
		m_ModelMatrix = glm::rotate(m_ModelMatrix, glm::radians(m_Rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		
		// 1st scale
		m_ModelMatrix = glm::scale(m_ModelMatrix, m_Scale);
	}
}