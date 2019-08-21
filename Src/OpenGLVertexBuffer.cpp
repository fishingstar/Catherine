#include "OpenGLVertexBuffer.h"
#include "OpenGLCommon.h"

namespace Catherine
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size, Usage usage) :
		IVertexBuffer(size, usage)
	{
		
	}

	bool OpenGLVertexBuffer::Initialize(const void * data)
	{
		return m_Buffer.Initialize(GL_ARRAY_BUFFER, GetUsage(), GetSize(), data);
	}

	void OpenGLVertexBuffer::Uninitialize()
	{
		m_Buffer.Uninitialize();
	}

	void OpenGLVertexBuffer::SetAttributeLayout(const std::vector<AttributeLayout> & attributes)
	{
		m_Buffer.Bind();

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
				(const void *)tmp_attribute.GetOffset()
			);
		}
	}

	void OpenGLVertexBuffer::Bind()
	{
		m_Buffer.Bind();
	}
}