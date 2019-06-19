#include <DemoRenderer.h>
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

		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		unsigned int VBO, EBO;
		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);
		// color attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

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
