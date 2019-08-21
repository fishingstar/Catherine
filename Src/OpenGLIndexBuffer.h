#pragma once

#include "IIndexBuffer.h"
#include "glad/glad.h"
#include "OpenGLBuffer.h"

namespace Catherine
{
	class OpenGLIndexBuffer : public IIndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint8_t stride, size_t size, Usage usage);

		bool Initialize(const void * data);
		void Uninitialize();

		void Bind();

	private:
		OpenGLBuffer m_Buffer;
	};
}