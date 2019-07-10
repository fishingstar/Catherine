#pragma once

#include <IIndexBuffer.h>
#include <glad/glad.h>

namespace Catherine
{
	class OpenGLIndexBuffer : public IIndexBuffer
	{
	public:
		OpenGLIndexBuffer(unsigned int stride, unsigned int size, unsigned int usage, const void * data = nullptr);

		void Bind();

	private:
		void CreateIndexBufferImp(unsigned int size, unsigned int usage, const void * data = nullptr);

	private:
		GLuint m_Resource;
	};
}