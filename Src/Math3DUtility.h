#pragma once

#include "glm/glm.hpp"

namespace Catherine
{
	class Math3DUtility
	{
	public:
		static glm::mat4x4 RotationMatrix(glm::vec3 rotation);

		static glm::vec3 RotationDirection(glm::vec3 rotation, glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f));
	};
}