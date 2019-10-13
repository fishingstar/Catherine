#pragma once

#include "IStorageBuffer.h"
#include "OpenGLBuffer.h"

namespace Catherine
{
	class OpenGLStorageBuffer : public IStorageBuffer
	{
	public:
		OpenGLStorageBuffer(size_t size, Usage usage);

		bool Initialize(const void* data);
		void Uninitialize();

		virtual void Bind(uint8_t slot) override;

	private:
		OpenGLBuffer m_Buffer;
	};
}