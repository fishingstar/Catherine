#pragma once

#include <glm/glm.hpp>

namespace Catherine
{
	class IMaterial
	{
	public:
		virtual bool Initialize(const char * param_Config) = 0;

		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value) = 0;

		virtual void Use() = 0;
	};
}