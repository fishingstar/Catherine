#include <Mesh.h>
#include <glad/glad.h>
#include <global.h>
#include <IVertexArray.h>

namespace Catherine
{
	void Mesh::Initialize(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index)
	{
		m_VertexCount = vertex.size();
		m_IndexCount = index.size();

		SetupBuffers(vertex, index);
	}

	void Mesh::Render()
	{
		m_VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
		m_VertexArray->UnBind();
	}

	void Mesh::SetupBuffers(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index)
	{
		m_VertexArray = g_Device->CreateVertexArray();

		m_VertexArray->Bind();

		std::vector<AttributeLayout> tmp_attributes;
		tmp_attributes.emplace_back(0, 3, ValueType::Float, false, sizeof(Vertex), 0);
		tmp_attributes.emplace_back(1, 3, ValueType::Float, false, sizeof(Vertex), 3 * sizeof(float));
		tmp_attributes.emplace_back(2, 2, ValueType::Float, false, sizeof(Vertex), 6 * sizeof(float));
		m_VertexBuffer = g_Device->CreateVertexBuffer(sizeof(Vertex) * vertex.size(), GL_STATIC_DRAW, &vertex[0], tmp_attributes);
		m_IndexBuffer = g_Device->CreateIndexBuffer(4, sizeof(unsigned int) * index.size(), GL_STATIC_DRAW, &index[0]);

		m_VertexArray->UnBind();
	}
}