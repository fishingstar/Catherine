#pragma once

#include <stdint.h>
#include "DeviceCommon.h"

namespace Catherine
{
	class IIndexBuffer
	{
	public:
		IIndexBuffer(uint8_t stride, size_t size, Usage usage) :
			m_Stride(stride),
			m_Size(size),
			m_Usage(usage)
		{ }

		uint8_t GetStride() const { return m_Stride; }
		size_t GetSize() const { return m_Size; }
		Usage GetUsage() const { return m_Usage; }

	private:
		uint8_t m_Stride;
		size_t m_Size;
		Usage m_Usage;
	};
}