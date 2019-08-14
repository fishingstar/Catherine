#include "Math3DUtility.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Catherine
{
	glm::mat4x4 Math3DUtility::RotationMatrix(const glm::vec3 & rotation)
	{
		glm::mat4x4 tmp_result = glm::mat4x4(1);
		tmp_result = glm::rotate(tmp_result, glm::radians(rotation.x), glm::vec3(-1.0f, 0.0f, 0.0f));
		tmp_result = glm::rotate(tmp_result, glm::radians(rotation.y), glm::vec3(0.0f, -1.0f, 0.0f));
		tmp_result = glm::rotate(tmp_result, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, -1.0f));
		return tmp_result;
	}

	glm::vec3 Math3DUtility::RotationDirection(const glm::vec3 & rotation, const glm::vec3 & forward)
	{
		glm::mat4x4 tmp_matrix = RotationMatrix(rotation);
		glm::vec4 tmp_result = tmp_matrix * glm::vec4(forward, 0.0f);
		return glm::vec3(tmp_result);
	}

	glm::mat4x4 Math3DUtility::GenViewMatrixFromDirection(const glm::vec3 & position, const glm::vec3 & direction)
	{
		glm::vec3 tmp_forward = direction;
		glm::vec3 tmp_right = glm::cross(tmp_forward, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::vec3 tmp_up = glm::cross(tmp_right, tmp_forward);
		glm::mat4x4 tmp_matrix = glm::lookAt(position, position + tmp_forward, tmp_up);
		return tmp_matrix;
	}

	glm::mat4x4 Math3DUtility::GenViewMatrixFromRotation(const glm::vec3 & position, const glm::vec3 & rotation)
	{
		return GenViewMatrixFromDirection(position, RotationDirection(rotation));
	}
}