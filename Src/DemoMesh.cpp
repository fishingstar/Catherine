#include <DemoMesh.h>
#include <VertexLayout.h>
#include <glad/glad.h>

namespace Catherine
{
	void DemoMesh::LoadFromFile(const char * param_Path)
	{
		float * vertices = new float[32] {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
		};

		unsigned int * indices = new unsigned int[6] {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		
		SetVertexBuffer(vertices, 32 * sizeof(float));
		SetIndexBuffer(indices, 6 * sizeof(unsigned int));
		SetElementIndex(true);

		VertexLayout * tmp_layout = GetVertexLayout();
		tmp_layout->AddAttribute(3, GL_FLOAT, false, 8 * sizeof(float), 0);
		tmp_layout->AddAttribute(3, GL_FLOAT, false, 8 * sizeof(float), 3 * sizeof(float));
		tmp_layout->AddAttribute(2, GL_FLOAT, false, 8 * sizeof(float), 6 * sizeof(float));
	}
}