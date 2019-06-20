#pragma once

#include <IMesh.h>

namespace Catherine
{
	class VertexLayout;

	class Mesh : public IMesh
	{
	public:
		Mesh();
		~Mesh();

		virtual void LoadFromFile(const char * param_Path) override;

		virtual const void * GetVertexBuffer(unsigned int & size) const override;
		virtual const void * GetIndexBuffer(unsigned int & size) const override;
		virtual const VertexLayout * GetVertexLayout() const override;

		virtual bool IsElementIndex() const;

	protected:
		VertexLayout * GetVertexLayout() { return m_Layout; }
		void SetElementIndex(bool index) { m_ElementIndex = index; }
		void SetVertexBuffer(void * param_Buffer, int size) { m_VertexBuffer = param_Buffer; m_VertexBufferSize = size; }
		void SetIndexBuffer(void * param_Buffer, int size) { m_IndexBuffer = param_Buffer; m_IndexBufferSize = size; }

	private:
		VertexLayout * m_Layout = nullptr;
		bool m_ElementIndex = false;

		unsigned int m_VertexBufferSize = 0;
		void * m_VertexBuffer = nullptr;

		unsigned int m_IndexBufferSize = 0;
		void * m_IndexBuffer = nullptr;
	};
}