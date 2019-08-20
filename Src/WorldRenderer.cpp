#include "WorldRenderer.h"
#include "IWorld.h"
#include "ForwardPipeline.h"
#include "LogUtility.h"

namespace Catherine
{
	bool WorldRenderer::Initialize()
	{
		m_ForwardPipeline = new ForwardPipeline();
		bool tmp_forwardInited = m_ForwardPipeline->Initialize();
		if (!tmp_forwardInited)
		{
			LogError("forward pipeline initialize failed...");
			return false;
		}

		return true;
	}

	void WorldRenderer::Uninitialize()
	{
		if (m_ForwardPipeline)
		{
			delete m_ForwardPipeline;
			m_ForwardPipeline = nullptr;
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
			m_ForwardPipeline->Render(worldContext);
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
