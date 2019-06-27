#pragma once

#include <IMesh.h>

namespace Catherine
{
	class Mesh : public IMesh
	{
	public:
		virtual void Initialize(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index) override;
		virtual void Render() override;

	private:
		void SetupBuffers(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index);

	private:
		size_t m_VertexCount = 0;
		size_t m_IndexCount = 0;

		// TODO: 这里用的OpenGL方式，需要封一层Buffer实现跨平台
		unsigned int m_VAO = 0;
		unsigned int m_VBO = 0;
		unsigned int m_IBO = 0;
	};
}