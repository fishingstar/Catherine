#include <Mesh.h>
#include <VertexLayout.h>

namespace Catherine
{
	Mesh::Mesh()
	{
		m_Layout = new VertexLayout();
	}

	Mesh::~Mesh()
	{
		if (m_Layout != nullptr)
		{
			delete m_Layout;
			m_Layout = nullptr;
		}
	}

	void Mesh::LoadFromFile(const char * param_Path)
	{

	}

	const void * Mesh::GetVertexBuffer(unsigned int & size) const
	{
		size = m_VertexBufferSize;
		return m_VertexBuffer;
	}

	const void * Mesh::GetIndexBuffer(unsigned int & size) const
	{
		size = m_ElementIndex ? m_IndexBufferSize : 0;
		return m_ElementIndex ? m_IndexBuffer : nullptr;
	}

	const VertexLayout * Mesh::GetVertexLayout() const
	{
		return m_Layout;
	}

	bool Mesh::IsElementIndex() const
	{
		return m_ElementIndex;
	}
}