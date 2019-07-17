#include "OpenGLIndexBuffer.h"
#include "OpenGLCommon.h"

namespace Catherine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(unsigned int stride, size_t size, Usage usage, const void * data) :
		IIndexBuffer(stride, size, usage)
	{
		CreateIndexBufferImp(size, usage, data);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Resource);
	}

	void OpenGLIndexBuffer::CreateIndexBufferImp(size_t size, Usage usage, const void * data)
	{
		glGenBuffers(1, &m_Resource);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Resource);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, OpenGLCommon::GetOpenGLUsage(usage));
	}
}