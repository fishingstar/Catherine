#pragma once

#include <IVertexBuffer.h>
#include <glad/glad.h>
#include <DeviceCommon.h>

namespace Catherine
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size, unsigned int usage, const void * data = nullptr);

		void Bind();
		void AddAttribute(unsigned int index, unsigned int count, ValueType type, unsigned int stride, unsigned int offset);

	private:
		void CreateVertexBufferImp(unsigned int size, unsigned int usage, const void * data);

	private:
		GLuint m_Resource;
	};
}