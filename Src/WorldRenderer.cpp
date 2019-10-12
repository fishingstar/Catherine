#include "WorldRenderer.h"
#include "IWorld.h"
#include "ForwardPipeline.h"
#include "DeferredPipeline.h"
#include "TileBasedDeferredPipeline.h"
#include "LogUtility.h"
#include "Setting.h"

namespace Catherine
{
	bool WorldRenderer::Initialize()
	{
		if (g_RenderPipeline == RenderPipeline::Forward)
			m_RenderPipeline = new ForwardPipeline();
		else if (g_RenderPipeline == RenderPipeline::Deferred)
			m_RenderPipeline = new DeferredPipeline();
		else if (g_RenderPipeline == RenderPipeline::TiledBasedDeferred)
			m_RenderPipeline = new TileBasedDeferredPipeline();

		bool tmp_Inited = m_RenderPipeline->Initialize();
		if (!tmp_Inited)
		{
			LogError("render pipeline initialize failed...");
			return false;
		}

		return true;
	}

	void WorldRenderer::Uninitialize()
	{
		if (m_RenderPipeline)
		{
			delete m_RenderPipeline;
			m_RenderPipeline = nullptr;
		}
	}

	void WorldRenderer::PreRender()
	{
		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			m_Worlds[i]->PreRender();
		}
	}

	void WorldRenderer::Render()
	{
		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			// collect render context
			m_Worlds[i]->Render();

			// send context to pipeline
			const WorldContext * worldContext = m_Worlds[i]->GetWorldContext();
			m_RenderPipeline->Render(worldContext);
		}
	}

	void WorldRenderer::PostRender()
	{
		for (size_t i = 0; i < m_Worlds.size(); i++)
		{
			m_Worlds[i]->PostRender();
		}
	}

	void WorldRenderer::RegisterWorld(IWorld * world)
	{
		if (world != nullptr)
		{
			m_Worlds.push_back(world);
		}
	}

	void WorldRenderer::UnRegisterWorld(IWorld * world)
	{
		if (world != nullptr)
		{
			auto tmp_iter = std::find(m_Worlds.begin(), m_Worlds.end(), world);
			if (tmp_iter != m_Worlds.end())
			{
				m_Worlds.erase(tmp_iter);
			}
		}
	}
}
