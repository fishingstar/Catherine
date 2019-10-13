#include "OpenGLStorageBuffer.h"

namespace Catherine
{
	OpenGLStorageBuffer::OpenGLStorageBuffer(size_t size, Usage usage) :
		IStorageBuffer(size, usage)
	{

	}

	bool OpenGLStorageBuffer::Initialize(const void * data)
	{
		return m_Buffer.Initialize(GL_SHADER_STORAGE_BUFFER, GetUsage(), GetSize(), data);
	}

	void OpenGLStorageBuffer::Uninitialize()
	{
		m_Buffer.Uninitialize();
	}

	void OpenGLStorageBuffer::Bind(uint8_t slot)
	{
		m_Buffer.Bind(slot);
	}
}