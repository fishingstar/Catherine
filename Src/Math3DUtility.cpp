#include "Math3DUtility.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Catherine
{
	glm::mat4x4 Math3DUtility::RotationMatrix(glm::vec3 rotation)
	{
		glm::mat4x4 tmp_result = glm::mat4x4(1);
		tmp_result = glm::rotate(tmp_result, glm::radians(rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		tmp_result = glm::rotate(tmp_result, glm::radians(rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
		tmp_result = glm::rotate(tmp_result, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
		return tmp_result;
	}

	glm::vec3 Math3DUtility::RotationDirection(glm::vec3 rotation, glm::vec3 forward)
	{
		glm::mat4x4 tmp_matrix = RotationMatrix(rotation);
		glm::vec4 tmp_result = tmp_matrix * glm::vec4(forward, 0.0f);
		return glm::vec3(tmp_result);
	}
}