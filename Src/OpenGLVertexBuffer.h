#pragma once

#include "IVertexBuffer.h"
#include "OpenGLBuffer.h"
#include "DeviceCommon.h"
#include "AttributeLayout.h"
#include <vector>

namespace Catherine
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		OpenGLVertexBuffer(size_t size, Usage usage);

		bool Initialize(const void * data);
		void Uninitialize();

		void SetAttributeLayout(const std::vector<AttributeLayout> & attributes);

		void Bind();

	private:
		OpenGLBuffer m_Buffer;
	};
}