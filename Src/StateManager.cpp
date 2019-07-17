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
}