#include "Exposure.h"
#include "IVertexArray.h"
#include "Material.h"
#include "IDevice.h"
#include "ISampler.h"
#include "IRenderTarget.h"

namespace Catherine
{
	extern IDevice* g_Device;

	const char* s_ExposureMaterial = "./res/material/exposure.mtl";

	bool Exposure::Initialize()
	{
		m_ExposureMaterial = new Material();
		m_ExposureMaterial->Initialize(s_ExposureMaterial);

		m_ExposureSampler = g_Device->CreateSampler();
		m_ExposureSampler->SetMinFilter(Filter::Nearest);
		m_ExposureSampler->SetMagFilter(Filter::Nearest);
		m_ExposureSampler->SetWrapS(WrapMode::Clamp_To_Edge);
		m_ExposureSampler->SetWrapT(WrapMode::Clamp_To_Edge);

		// temp code
		struct ScreenVertex
		{
			glm::vec3 Position;
			glm::vec2 Texcoord;
		};

		std::vector<ScreenVertex> tmp_vertexBuffer =
		{
			{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
			{ glm::vec3(1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
			{ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
			{ glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) }
		};

		std::vector<uint32_t> tmp_indexBuffer =
		{
			0, 1, 2,
			0, 2, 3
		};

		m_ScreenVertexArray = g_Device->CreateVertexArray();
		m_ScreenVertexArray->Bind();

		std::vector<AttributeLayout> tmp_attributes;
		tmp_attributes.emplace_back(0, 3, ValueType::Float, false, sizeof(ScreenVertex), 0);
		tmp_attributes.emplace_back(1, 2, ValueType::Float, false, sizeof(ScreenVertex), 3 * sizeof(float));
		auto tmp_vertex = g_Device->CreateVertexBuffer(sizeof(ScreenVertex) * tmp_vertexBuffer.size(), Usage::Static_Draw, &tmp_vertexBuffer[0], tmp_attributes);
		// only support 4 byte(32bit) stride index for now, 2 byte(16bit) in the future
		auto tmp_index = g_Device->CreateIndexBuffer(4, sizeof(uint32_t) * tmp_indexBuffer.size(), Usage::Static_Draw, &tmp_indexBuffer[0]);

		m_ScreenVertexArray->UnBind();
		m_ScreenVertexArray->SetVertexCount(tmp_vertexBuffer.size());
		m_ScreenVertexArray->SetIndexCount(tmp_indexBuffer.size());

		return true;
	}

	void Exposure::Uninitialize()
	{
		
	}

	void Exposure::Process(IRenderTarget * src, IRenderTarget * dst)
	{
		dst->Bind();
		{
			ITexture* tmp_srcTexture = src->GetColorAttachment(0);

			m_ExposureMaterial->SetTexture("Tex0", tmp_srcTexture);
			m_ExposureMaterial->SetSampler("Tex0", m_ExposureSampler);
			m_ExposureMaterial->Use(ShaderPass::Forward);

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}
}