#include "StateManager.h"
#include "IDevice.h"

namespace Catherine
{
	extern IDevice * g_Device;

	StateManager * StateManager::Instance()
	{
		static StateManager s_instance;
		return &s_instance;
	}

	void StateManager::EnableDepthTest(bool enabled)
	{
		g_Device->EnableDepthTest(enabled);
	}

	void StateManager::SetDepthTestMode(DepthTestMode mode)
	{
		g_Device->SetDepthTestMode(mode);
	}

	void StateManager::EnableCullFace(bool enabled)
	{
		g_Device->EnableCullFace(enabled);
	}

	void StateManager::SetCullFaceMode(CullFaceMode mode)
	{
		g_Device->SetCullFaceMode(mode);
	}

	void StateManager::EnableBlend(bool enabled)
	{
		g_Device->EnableBlend(enabled);
	}

	void StateManager::SetBlendEquation(BlendEquation equation)
	{
		g_Device->SetBlendEquation(equation);
	}

	void StateManager::SetBlendFunc(BlendFunc src, BlendFunc dst, BlendFunc src_alpha, BlendFunc dst_alpha)
	{
		g_Device->SetBlendFunc(src, dst, src_alpha, dst_alpha);
	}
}