#include "Bloom.h"
#include "RenderTargetManager.h"
#include "DeviceConst.h"
#include "IRenderTarget.h"
#include "IDevice.h"
#include "Material.h"
#include "IVertexArray.h"
#include "ISampler.h"

namespace Catherine
{
	extern IDevice * g_Device;

	const char * s_BloomMaterial = "./res/material/bloom.mtl";

	bool Bloom::Initialize()
	{
		m_PingRenderTarget = RenderTargetManager::Instance()->CreateRenderTarget(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 1, false, false);
		m_PongRenderTarget = RenderTargetManager::Instance()->CreateRenderTarget(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 1, false, false);

		m_BloomMaterial = new Material();
		m_BloomMaterial->Initialize(s_BloomMaterial);

		m_BloomSampler = g_Device->CreateSampler();
		m_BloomSampler->SetMinFilter(Filter::Nearest);
		m_BloomSampler->SetMagFilter(Filter::Nearest);
		m_BloomSampler->SetWrapS(WrapMode::Clamp_To_Edge);
		m_BloomSampler->SetWrapT(WrapMode::Clamp_To_Edge);


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

	void Bloom::Uninitialize()
	{
		RenderTargetManager::Instance()->DeleteRenderTarget(m_PingRenderTarget);
		RenderTargetManager::Instance()->DeleteRenderTarget(m_PongRenderTarget);
	}

	void Bloom::Process(IRenderTarget * src, IRenderTarget * dst)
	{
		RenderBloomArea(src, m_PingRenderTarget);
		for (size_t i = 0; i < 5; ++i)
		{
			RenderBloomBlurHorizontal(m_PingRenderTarget, m_PongRenderTarget);
			RenderBloomBlurVertical(m_PongRenderTarget, m_PingRenderTarget);
		}
		RenderBloomResult(m_PingRenderTarget, src, dst);
	}

	void Bloom::RenderBloomArea(IRenderTarget * src, IRenderTarget * dst)
	{
		dst->Bind();
		{
			// clear screen
			g_Device->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			g_Device->Clear((BitField)BufferBit::All);

			ITexture * tmp_srcTexture = src->GetColorAttachment(0);

			m_BloomMaterial->SetInt("stage", 0);
			m_BloomMaterial->SetTexture("Tex0", tmp_srcTexture);
			m_BloomMaterial->SetSampler("Tex0", m_BloomSampler);
			m_BloomMaterial->Use(ShaderPass::Forward);

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}

	void Bloom::RenderBloomBlurHorizontal(IRenderTarget * src, IRenderTarget * dst)
	{
		dst->Bind();
		{
			// clear screen
			g_Device->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			g_Device->Clear((BitField)BufferBit::All);

			ITexture * tmp_srcTexture = src->GetColorAttachment(0);

			m_BloomMaterial->SetInt("stage", 1);
			m_BloomMaterial->SetTexture("Tex0", tmp_srcTexture);
			m_BloomMaterial->SetSampler("Tex0", m_BloomSampler);
			m_BloomMaterial->Use(ShaderPass::Forward);

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}

	void Bloom::RenderBloomBlurVertical(IRenderTarget * src, IRenderTarget * dst)
	{
		dst->Bind();
		{
			// clear screen
			g_Device->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			g_Device->Clear((BitField)BufferBit::All);

			ITexture * tmp_srcTexture = src->GetColorAttachment(0);

			m_BloomMaterial->SetInt("stage", 2);
			m_BloomMaterial->SetTexture("Tex0", tmp_srcTexture);
			m_BloomMaterial->SetSampler("Tex0", m_BloomSampler);
			m_BloomMaterial->Use(ShaderPass::Forward);

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}

	void Bloom::RenderBloomResult(IRenderTarget * src, IRenderTarget * origin, IRenderTarget * dst)
	{
		dst->Bind();
		{
			ITexture * tmp_srcTexture = src->GetColorAttachment(0);
			ITexture * tmp_originTexture = origin->GetColorAttachment(0);

			m_BloomMaterial->SetInt("stage", 3);
			m_BloomMaterial->SetTexture("Tex0", tmp_srcTexture);
			m_BloomMaterial->SetSampler("Tex0", m_BloomSampler);
			m_BloomMaterial->SetTexture("Origin", tmp_originTexture);
			m_BloomMaterial->SetSampler("Origin", m_BloomSampler);
			m_BloomMaterial->Use(ShaderPass::Forward);

			m_ScreenVertexArray->Bind();

			// draw command
			g_Device->DrawElement(DrawMode::TRIANGLES, m_ScreenVertexArray->GetIndexCount(), ValueType::UInt, 0);

			m_ScreenVertexArray->UnBind();
		}
	}
}