#pragma once

#include "IVertexArray.h"
#include "glad/glad.h"

namespace Catherine
{
	class OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();

		virtual void Bind() override;
		virtual void UnBind() override;

		virtual void SetVertexCount(size_t count) override { m_VertexCount = count; }
		virtual size_t GetVertexCount() const override { return m_VertexCount; }

		virtual void SetIndexCount(size_t count) override { m_IndexCount = count; }
		virtual size_t GetIndexCount() const override { return m_IndexCount; }

	private:
		void CreateVertexArrayImp();

	private:
		GLenum m_Resource;

		size_t m_VertexCount = 0;
		size_t m_IndexCount = 0;
	};
}