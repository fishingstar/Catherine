#pragma once

namespace Catherine
{
	class IVertexBuffer
	{
	public:
		IVertexBuffer(size_t size, unsigned int usage) :
			m_Size(size),
			m_Usage(usage)
		{

		}

		size_t GetSize() const { return m_Size; }
		unsigned int GetUsage() const { return m_Usage; }

	private:
		size_t m_Size;
		unsigned int m_Usage;
	};
}