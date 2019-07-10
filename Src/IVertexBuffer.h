#pragma once

namespace Catherine
{
	class IVertexBuffer
	{
	public:
		IVertexBuffer(unsigned int size, unsigned int usage) :
			m_Size(size),
			m_Usage(usage)
		{

		}

		unsigned int GetSize() const { return m_Size; }
		unsigned int GetUsage() const { return m_Usage; }

	private:
		unsigned int m_Size;
		unsigned int m_Usage;
	};
}