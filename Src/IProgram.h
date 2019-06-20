#pragma once

#include <glm/glm.hpp>

namespace Catherine
{
	class IProgram
	{
	public:
		// TODO : support other shader types
		virtual void AttachShader(const char * vertex, const char * fragment) = 0;
		virtual bool Compile() = 0;
		virtual bool Link() = 0;
		virtual void Use() = 0;

		virtual void SetBool(const char * key, bool value) = 0;
		virtual void SetInt(const char * key, int value) = 0;
		virtual void SetFloat(const char * key, float value) = 0;
		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value) = 0;
	};
}
