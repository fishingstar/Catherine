#include <Mesh.h>
#include <glad/glad.h>

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
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Mesh::SetupBuffers(const std::vector<Vertex> & vertex, const std::vector<unsigned int> & index)
	{
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);
		glGenBuffers(1, &m_IBO);

		// vertex array ->
		glBindVertexArray(m_VAO);

		// vertex attribute
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), &vertex[0], GL_STATIC_DRAW);

		// vertex index
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * index.size(), &index[0], GL_STATIC_DRAW);

		// position attribute
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

		// normal attribute
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(3 * sizeof(float)));

		// texcoord attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)(6 * sizeof(float)));

		// vertex array end <-
		glBindVertexArray(0);
	}
}