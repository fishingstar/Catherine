#pragma once

#include "glm/glm.hpp"

namespace Catherine
{
	class Math3DUtility
	{
	public:
		static glm::mat4x4 RotationMatrix(const glm::vec3 & rotation);
		static glm::vec3 RotationDirection(const glm::vec3 & rotation, const glm::vec3 & forward = glm::vec3(0.0f, 0.0f, -1.0f));

		static glm::mat4x4 GenViewMatrixFromDirection(const glm::vec3 & position, const glm::vec3 & direction);
		static glm::mat4x4 GenViewMatrixFromRotation(const glm::vec3 & position, const glm::vec3 & rotation);
	};
}