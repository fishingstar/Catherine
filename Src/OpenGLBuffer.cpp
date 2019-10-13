#include "OpenGLBuffer.h"
#include "OpenGLCommon.h"

namespace Catherine
{
	bool OpenGLBuffer::Initialize(GLenum target, Usage usage, size_t size, const void * data)
	{
		m_Target = target;
		m_Usage = OpenGLCommon::GetOpenGLUsage(usage);

		glGenBuffers(1, &m_Resource);
		glBindBuffer(m_Target, m_Resource);
		glBufferData(m_Target, size, data, m_Usage);

		return true;
	}

	void OpenGLBuffer::Uninitialize()
	{
		glDeleteBuffers(1, &m_Resource);
	}

	void OpenGLBuffer::Bind()
	{
		glBindBuffer(m_Target, m_Resource);
	}

	void OpenGLBuffer::Bind(uint8_t slot)
	{
		glBindBufferBase(m_Target, slot, m_Resource);
	}
}