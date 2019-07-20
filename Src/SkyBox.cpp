#include "Skybox.h"
#include "IDevice.h"
#include "IVertexArray.h"
#include "glm/glm.hpp"
#include "RenderContext.h"
#include "WorldContext.h"
#include "Material.h"

namespace Catherine
{
	extern IDevice * g_Device;

	struct SkyBoxVertex
	{
		glm::vec3 Position;
	};

	std::vector<glm::vec3> vertex = {
		// positions          
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),

		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
	};

	std::vector<unsigned int> index = {
		0, 1, 2,
		2, 3, 0,
		
		6, 5, 4,
		4, 7, 6,

		2, 6, 7,
		7, 3, 2,

		5, 1, 0,
		0, 4, 5,

		7, 4, 0,
		0, 3, 7,

		6, 2, 1,
		1, 5, 6
	};

	bool Skybox::Initialize()
	{
		m_VertexArray = g_Device->CreateVertexArray();

		m_VertexArray->Bind();

		std::vector<AttributeLayout> tmp_attributes;
		tmp_attributes.emplace_back(0, 3, ValueType::Float, false, sizeof(SkyBoxVertex), 0);

		m_VertexBuffer = g_Device->CreateVertexBuffer(sizeof(SkyBoxVertex) * vertex.size(), Usage::Static_Draw, &vertex[0], tmp_attributes);
		// only support 4 byte(32bit) stride index for now, 2 byte(16bit) in the future
		m_IndexBuffer = g_Device->CreateIndexBuffer(4, sizeof(unsigned int) * index.size(), Usage::Static_Draw, &index[0]);

		m_VertexArray->UnBind();

		m_VertexArray->SetVertexCount(vertex.size());
		m_VertexArray->SetIndexCount(index.size());



		m_Material = new Material();
		m_Material->Initialize("./res/material/skybox.mtl");


		m_Context = new RenderContext();
		m_Context->SetVertexArray(m_VertexArray);
		m_Context->SetMaterial(m_Material);

		return true;
	}

	void Skybox::Uninitialize()
	{

	}

	void Skybox::Render(WorldContext * context)
	{
		context->AddRenderContext(m_Context);
	}
}