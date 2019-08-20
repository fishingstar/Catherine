#include "RenderTargetManager.h"
#include "IDevice.h"
#include "IRenderTarget.h"
#include "DeviceConst.h"
#include <algorithm>

namespace Catherine
{
	extern IDevice * g_Device;

	RenderTargetManager * RenderTargetManager::Instance()
	{
		static RenderTargetManager s_instance;
		return &s_instance;
	}

	IRenderTarget * RenderTargetManager::GetDefaultRenderTarget()
	{
		if (m_DefaultRenderTarget == nullptr)
		{
			m_DefaultRenderTarget = CreateRenderTarget(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, 0, false, false);
		}
		return m_DefaultRenderTarget;
	}

	IRenderTarget * RenderTargetManager::CreateRenderTarget(uint32_t width, uint32_t height, uint8_t color_count, bool depth, bool stencil)
	{
		IRenderTarget * tmp_result = g_Device->CreateRenderTarget();

		if (tmp_result)
		{
			bool tmp_inited = tmp_result->Initialize(width, height, color_count, depth, stencil);
			if (!tmp_inited)
			{
				DeleteRenderTarget(tmp_result);
				tmp_result = nullptr;
			}
			else
			{
				m_RenderTargets.push_back(tmp_result);
			}
		}
		
		return tmp_result;
	}

	void RenderTargetManager::DeleteRenderTarget(IRenderTarget * rt)
	{
		if (rt != nullptr)
		{
			auto tmp_iter = std::find(m_RenderTargets.begin(), m_RenderTargets.end(), rt);
			if (tmp_iter != m_RenderTargets.end())
			{
				m_RenderTargets.erase(tmp_iter);
			}
			delete rt;
		}
	}
}