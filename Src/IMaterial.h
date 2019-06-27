#pragma once

#include <glm/glm.hpp>

namespace Catherine
{
	class IMaterial
	{
	public:
		virtual bool Initialize(const char * param_Config) = 0;

		virtual void SetInt(const char * key, int value) = 0;
		virtual void SetFloat(const char * key, float value) = 0;
		virtual void SetVec2(const char * key, const glm::vec2 & value) = 0;
		virtual void SetVec3(const char * key, const glm::vec3 & value) = 0;
		virtual void SetVec4(const char * key, const glm::vec4 & value) = 0;
		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value) = 0;

		virtual void Use() = 0;
	};
}