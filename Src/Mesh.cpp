#include "Mesh.h"
#include "IDevice.h"
#include "IVertexArray.h"
#include "RenderContext.h"

namespace Catherine
{
	extern IDevice * g_Device;

	void Mesh::Initialize(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index)
	{
		SetupBuffers(vertex, index);

		m_Context = new RenderContext();
		m_Context->SetVertexArray(m_VertexArray);
	}

	void Mesh::SetupBuffers(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index)
	{
		m_VertexArray = g_Device->CreateVertexArray();

		m_VertexArray->Bind();

		std::vector<AttributeLayout> tmp_attributes;
		tmp_attributes.emplace_back(0, 3, ValueType::Float, false, sizeof(Vertex), 0);
		tmp_attributes.emplace_back(1, 3, ValueType::Float, false, sizeof(Vertex), 3 * sizeof(float));
		tmp_attributes.emplace_back(2, 3, ValueType::Float, false, sizeof(Vertex), 6 * sizeof(float));
		tmp_attributes.emplace_back(3, 2, ValueType::Float, false, sizeof(Vertex), 9 * sizeof(float));

		m_VertexBuffer = g_Device->CreateVertexBuffer(sizeof(Vertex) * vertex.size(), Usage::Static_Draw, &vertex[0], tmp_attributes);
		// only support 4 byte(32bit) stride index for now, 2 byte(16bit) in the future
		m_IndexBuffer = g_Device->CreateIndexBuffer(4, sizeof(unsigned int) * index.size(), Usage::Static_Draw, &index[0]);

		m_VertexArray->UnBind();

		m_VertexArray->SetVertexCount(vertex.size());
		m_VertexArray->SetIndexCount(index.size());
	}
}