#pragma once

#include <IMesh.h>

namespace Catherine
{
	class IVertexArray;
	class IVertexBuffer;
	class IIndexBuffer;
	class RenderContext;

	class Mesh : public IMesh
	{
	public:
		virtual void Initialize(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index) override;
		virtual RenderContext * GetRenderContext() const { return m_Context; }
		virtual IVertexArray * GetVertexArray() const { return m_VertexArray; }

	private:
		void SetupBuffers(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index);

	private:
		IVertexArray * m_VertexArray = nullptr;
		IVertexBuffer * m_VertexBuffer = nullptr;
		IIndexBuffer * m_IndexBuffer = nullptr;

		RenderContext * m_Context;
	};
}