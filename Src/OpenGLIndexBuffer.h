#pragma once

#include "IIndexBuffer.h"
#include "glad/glad.h"

namespace Catherine
{
	class OpenGLIndexBuffer : public IIndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int stride, size_t size, Usage usage, const void * data = nullptr);

		void Bind();

	private:
		void CreateIndexBufferImp(size_t size, Usage usage, const void * data = nullptr);

	private:
		GLuint m_Resource;
	};
}