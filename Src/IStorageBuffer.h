#pragma once

#include "DeviceCommon.h"

namespace Catherine
{
	class IStorageBuffer
	{
	public:
		IStorageBuffer(size_t size, Usage usage) :
			m_Size(size),
			m_Usage(usage)
		{ }

		virtual void Bind(uint8_t slot) = 0;

	public:
		size_t GetSize() const { return m_Size; }
		Usage GetUsage() const { return m_Usage; }

	private:
		size_t m_Size;
		Usage m_Usage;
	};
}