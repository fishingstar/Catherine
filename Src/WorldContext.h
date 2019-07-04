#pragma once

#include <vector>

namespace Catherine
{
	class RenderContext;
	class CameraContext;
	class LightContext;

	class WorldContext
	{
	public:
		void AddRenderContext(RenderContext * context);
		void ClearRenderContext();
		const std::vector<RenderContext *> & GetRenderContexts() const;

		void SetCameraContext(CameraContext * context);
		void SetLightContext(LightContext * context);

	private:
		// collected render context in levels
		std::vector<RenderContext *> m_RenderContexts;
		// camera context
		CameraContext * m_CameraContext = nullptr;
		// light context
		LightContext * m_LightContext = nullptr;
	};
}