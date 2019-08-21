#include "OpenGLIndexBuffer.h"
#include "OpenGLCommon.h"

namespace Catherine
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint8_t stride, size_t size, Usage usage) :
		IIndexBuffer(stride, size, usage)
	{
		
	}

	bool OpenGLIndexBuffer::Initialize(const void * data)
	{
		return m_Buffer.Initialize(GL_ELEMENT_ARRAY_BUFFER, GetUsage(), GetSize(), data);
	}

	void OpenGLIndexBuffer::Uninitialize()
	{
		m_Buffer.Uninitialize();
	}

	void OpenGLIndexBuffer::Bind()
	{
		m_Buffer.Bind();
	}
}