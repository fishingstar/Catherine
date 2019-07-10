#pragma once

namespace Catherine
{
	class IMaterial;
	class IVertexArray;

	class RenderContext
	{
	public:
		void SetMaterial(IMaterial * material) { m_Material = material; }
		IMaterial * GetMaterial() const { return m_Material; }

		void SetVertexArray(IVertexArray * va) { m_VertexArray = va; }
		IVertexArray * GetVertexArray() const { return m_VertexArray; }

	private:
		IMaterial * m_Material = nullptr;
		IVertexArray * m_VertexArray = nullptr;
	};
}