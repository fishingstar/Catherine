#include <OpenGLVertexBuffer.h>
#include <OpenGLCommon.h>

namespace Catherine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, Usage usage, const void * data, const std::vector<AttributeLayout> & attributes) :
		IVertexBuffer(size, usage),
		m_Attributes(attributes)
	{
		CreateVertexBufferImp(size, usage, data, attributes);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_Resource);
	}

	void OpenGLVertexBuffer::CreateVertexBufferImp(size_t size, Usage usage, const void * data, const std::vector<AttributeLayout> & attributes)
	{
		glGenBuffers(1, &m_Resource);
		glBindBuffer(GL_ARRAY_BUFFER, m_Resource);
		glBufferData(GL_ARRAY_BUFFER, size, data, OpenGLCommon::GetOpenGLUsage(usage));

		for (size_t i = 0; i < attributes.size(); i++)
		{
			const AttributeLayout & tmp_attribute = attributes[i];

			glEnableVertexAttribArray(tmp_attribute.GetIndex());
			glVertexAttribPointer(
				tmp_attribute.GetIndex(),
				tmp_attribute.GetCount(),
				OpenGLCommon::GetOpenGLType(tmp_attribute.GetValueType()),
				tmp_attribute.GetNormalized(),
				tmp_attribute.GetStride(),
				(void *)tmp_attribute.GetOffset()
			);
		}
	}
}