#pragma once

#include <stdint.h>
#include "glad/glad.h"
#include "DeviceCommon.h"

namespace Catherine
{
	class OpenGLBuffer
	{
	public:
		bool Initialize(GLenum target, Usage usage, size_t size, const void * data = nullptr);
		void Uninitialize();

		void Bind();

	private:
		GLenum m_Target;
		GLenum m_Usage;
		GLuint m_Resource;
	};
}