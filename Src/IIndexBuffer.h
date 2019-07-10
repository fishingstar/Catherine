#pragma once

#include <DeviceCommon.h>

namespace Catherine
{
	class IIndexBuffer
	{
	public:
		IIndexBuffer(unsigned int stride, size_t size, Usage usage) :
			m_Stride(stride),
			m_Size(size),
			m_Usage(usage)
		{ }

		unsigned int GetStride() const { return m_Stride; }
		size_t GetSize() const { return m_Size; }
		Usage GetUsage() const { return m_Usage; }

	private:
		unsigned int m_Stride;
		size_t m_Size;
		Usage m_Usage;
	};
}