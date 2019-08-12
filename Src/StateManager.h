#pragma once

#include "DeviceCommon.h"

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

		void EnableBlend(bool enabled);
		void SetBlendEquation(BlendEquation equation);
		void SetBlendFunc(BlendFunc src, BlendFunc dst, BlendFunc src_alpha, BlendFunc dst_alpha);

	private:
		StateManager() { }

	private:
		// TODO : cache current device render state to reduce state switches....

	};
}