#pragma once

namespace Catherine
{
	class IIndexBuffer
	{
	public:
		IIndexBuffer(unsigned int stride, size_t size, unsigned int usage) :
			m_Stride(stride),
			m_Size(size),
			m_Usage(usage)
		{ }

		unsigned int GetStride() const { return m_Stride; }
		size_t GetSize() const { return m_Size; }
		unsigned int GetUsage() const { return m_Usage; }

	private:
		unsigned int m_Stride;
		size_t m_Size;
		unsigned int m_Usage;
	};
}