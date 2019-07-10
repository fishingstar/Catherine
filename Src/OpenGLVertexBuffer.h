#pragma once

#include <IVertexBuffer.h>
#include <glad/glad.h>
#include <DeviceCommon.h>
#include <AttributeLayout.h>
#include <vector>

namespace Catherine
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		OpenGLVertexBuffer(unsigned int size, unsigned int usage, const void * data, const std::vector<AttributeLayout> & attributes);

		void Bind();

	private:
		void CreateVertexBufferImp(unsigned int size, unsigned int usage, const void * data, const std::vector<AttributeLayout> & attributes);

	private:
		GLuint m_Resource;

		std::vector<AttributeLayout> m_Attributes;
	};
}