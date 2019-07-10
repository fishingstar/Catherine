#include <OpenGLVertexArray.h>

namespace Catherine
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		CreateVertexArrayImp();
	}

	void OpenGLVertexArray::CreateVertexArrayImp()
	{
		glGenVertexArrays(1, &m_Resource);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_Resource);
	}

	void OpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}
}