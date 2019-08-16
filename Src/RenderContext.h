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

		// cast shadow properties
		bool GetCastShadow() const { return m_CastShadow; }
		void SetCastShadow(bool value) { m_CastShadow = value; }

		// receive shadow properties
		bool GetReceiveShadow() const { return m_ReceiveShadow; }
		void SetReceiveShadow(bool value) { m_ReceiveShadow = value; }

	private:
		IMaterial * m_Material = nullptr;
		IVertexArray * m_VertexArray = nullptr;

		bool m_CastShadow = true;
		bool m_ReceiveShadow = true;
	};
}