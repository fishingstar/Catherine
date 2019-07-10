#pragma once

#include <IMesh.h>

namespace Catherine
{
	class IVertexArray;
	class IVertexBuffer;
	class IIndexBuffer;

	class Mesh : public IMesh
	{
	public:
		virtual void Initialize(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index) override;
		virtual void Render(WorldContext * context) override;

	private:
		void SetupBuffers(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index);

	private:
		size_t m_VertexCount = 0;
		size_t m_IndexCount = 0;

		IVertexArray * m_VertexArray = nullptr;
		IVertexBuffer * m_VertexBuffer = nullptr;
		IIndexBuffer * m_IndexBuffer = nullptr;
	};
}