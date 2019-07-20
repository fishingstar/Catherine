#pragma once

namespace Catherine
{
	class RenderContext;
	class WorldContext;
	class IMaterial;
	class IVertexArray;
	class IVertexBuffer;
	class IIndexBuffer;

	class Skybox
	{
	public:
		bool Initialize();
		void Uninitialize();

		void Render(WorldContext * context);

	private:
		RenderContext * m_Context;

		IMaterial * m_Material;

		IVertexArray * m_VertexArray = nullptr;
		IVertexBuffer * m_VertexBuffer = nullptr;
		IIndexBuffer * m_IndexBuffer = nullptr;
	};
}