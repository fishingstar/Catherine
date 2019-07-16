#pragma once

#include <DeviceCommon.h>

namespace Catherine
{
	class StateManager
	{
	public:
		static StateManager * Instance();

		void EnableDepthTest(bool enabled);
		void SetDepthTestMode(DepthTestMode mode);

		void EnableCullFace(bool enabled);
		void SetCullFaceMode(CullFaceMode mode);

	private:
		StateManager() { }

	private:
		// TODO : cache current device render state to reduce state switches....

	};
}