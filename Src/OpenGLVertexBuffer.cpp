#include <OpenGLVertexBuffer.h>

namespace Catherine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(unsigned int size, unsigned int usage, const void * data) :
		IVertexBuffer(size, usage)
	{
		CreateVertexBufferImp(size, usage, data);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Resource);
	}

	void OpenGLVertexBuffer::AddAttribute(unsigned int index, unsigned int count, ValueType type, unsigned int stride, unsigned int offset)
	{

	}

	void OpenGLVertexBuffer::CreateVertexBufferImp(unsigned int size, unsigned int usage, const void * data)
	{
		glGenBuffers(1, &m_Resource);
		glBindBuffer(GL_ARRAY_BUFFER, m_Resource);
		glBufferData(GL_ARRAY_BUFFER, size, data, usage);
	}
}