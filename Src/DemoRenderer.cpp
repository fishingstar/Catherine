#include <DemoRenderer.h>
#include <DemoMesh.h>
#include <VertexLayout.h>
#include <OpenGLProgram.h>
#include <OpenGLTexture.h>
#include <Material.h>
#include <Camera.h>
#include <global.h>

namespace Catherine
{
	extern IDevice * g_Device;

	bool DemoRenderer::Initialize()
	{
		m_Camera = new Camera();
		m_Camera->SetPosition(1.0f, 1.0, 1.0f);
		m_Camera->SetRotate(45.0f, -45.0f, 0.0f);
		m_Camera->SetProjectionMode(ProjectionMode::Persperctive);
		m_Camera->SetClearColor(glm::vec3(0.2f, 0.3f, 0.4f));

		IMesh * tmp_mesh = new DemoMesh();
		tmp_mesh->LoadFromFile(nullptr);

		unsigned int tmp_vertexSize = 0;
		const void * tmp_vertex = tmp_mesh->GetVertexBuffer(tmp_vertexSize);
		unsigned int tmp_indexSize = 0;
		const void * tmp_index = tmp_mesh->GetIndexBuffer(tmp_indexSize);
		const VertexLayout * tmp_layout = tmp_mesh->GetVertexLayout();

		unsigned int VBO;
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, tmp_vertexSize, tmp_vertex, GL_STATIC_DRAW);

		unsigned int tmp_count = tmp_layout->Count();
		for (unsigned int i = 0; i < tmp_count; ++i)
		{
			const VertexLayout::AttributeItem & tmp_item = tmp_layout->GetItem(i);
			glVertexAttribPointer(i, tmp_item.count, tmp_item.type, tmp_item.normalized, tmp_item.stride, (void *)tmp_item.offset);
			glEnableVertexAttribArray(i);
		}

		m_Material = new Material();
		m_Material->Initialize(nullptr);

		g_Device->SetFrontFace(FrontFaceMode::CounterClockwise);

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
		const glm::vec3 & tmp_color = m_Camera->GetClearColor();
		g_Device->ClearColor(tmp_color.r, tmp_color.g, tmp_color.b, 1.0f);
		g_Device->Clear();

		const glm::mat4x4 & tmp_view = m_Camera->GetViewMatrix();
		const glm::mat4x4 & tmp_projection = m_Camera->GetProjectionMatrix();
		m_Material->SetMat4x4("view", tmp_view);
		m_Material->SetMat4x4("projection", tmp_projection);
		m_Material->Use();

		glBindVertexArray(m_VAO);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void DemoRenderer::PostRender()
	{

	}
}
