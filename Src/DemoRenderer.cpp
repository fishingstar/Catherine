#include <DemoRenderer.h>
#include <DemoMesh.h>
#include <VertexLayout.h>
#include <OpenGLProgram.h>
#include <OpenGLTexture.h>
#include <global.h>

namespace Catherine
{
	extern IDevice * g_Device;

	bool DemoRenderer::Initialize()
	{
		m_Program = new GLProgram();
		m_Program->AttachShader("./res/shader/simple.vs", "./res/shader/simple.fs");
		m_Program->Compile();
		m_Program->Link();

		m_Program->Use();
		m_Program->SetInt("diffuse1", 0);
		m_Program->SetInt("diffuse2", 1);

		g_Device->ClearColor(0.2f, 0.3f, 0.4f, 1.0f);

		IMesh * tmp_mesh = new DemoMesh();
		tmp_mesh->LoadFromFile(nullptr);

		unsigned int tmp_vertexSize = 0;
		const void * tmp_vertex = tmp_mesh->GetVertexBuffer(tmp_vertexSize);
		unsigned int tmp_indexSize = 0;
		const void * tmp_index = tmp_mesh->GetIndexBuffer(tmp_indexSize);
		const VertexLayout * tmp_layout = tmp_mesh->GetVertexLayout();

		unsigned int VBO, EBO;
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tmp_vertexSize, tmp_vertex, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, tmp_indexSize, tmp_index, GL_STATIC_DRAW);

		unsigned int tmp_count = tmp_layout->Count();
		for (unsigned int i = 0; i < tmp_count; ++i)
		{
			const VertexLayout::AttributeItem & tmp_item = tmp_layout->GetItem(i);
			glVertexAttribPointer(i, tmp_item.count, tmp_item.type, tmp_item.normalized, tmp_item.stride, (void *)tmp_item.offset);
			glEnableVertexAttribArray(i);
		}

		m_Texture1 = new GLTexture();
		m_Texture1->LoadFromFile("./res/texture/wall.jpg");

		m_Texture2 = new GLTexture();
		m_Texture2->LoadFromFile("./res/texture/container.jpg");

		return true;
	}

	void DemoRenderer::Uninitialize()
	{

	}

	void DemoRenderer::PreRender()
	{

	}

	void DemoRenderer::Render()
	{
		g_Device->Clear();

		m_Texture1->Use(0);
		m_Texture2->Use(1);

		m_Program->Use();

		glBindVertexArray(m_VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	void DemoRenderer::PostRender()
	{

	}
}
