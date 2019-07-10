#pragma once

#include <DeviceCommon.h>

namespace Catherine
{
	class IVertexBuffer
	{
	public:
		IVertexBuffer(size_t size, Usage usage) :
			m_Size(size),
			m_Usage(usage)
		{

		}

		size_t GetSize() const { return m_Size; }
		Usage GetUsage() const { return m_Usage; }

	private:
		size_t m_Size;
		Usage m_Usage;
	};
}