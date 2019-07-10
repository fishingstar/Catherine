#pragma once

#include <IVertexArray.h>
#include <glad/glad.h>

namespace Catherine
{
	class OpenGLVertexArray : public IVertexArray
	{
	public:
		OpenGLVertexArray();

		virtual void Bind() override;
		virtual void UnBind() override;

	private:
		void CreateVertexArrayImp();

	private:
		GLenum m_Resource;
	};
}