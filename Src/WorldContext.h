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

		std::vector<RenderContext *> GetRenderContexts() { return m_RenderContexts; }
		const std::vector<RenderContext *> & GetRenderContexts() const { return m_RenderContexts; }

		const CameraContext * GetCameraContext() const { return m_CameraContext; }
		void SetCameraContext(CameraContext * context) { m_CameraContext = context; }

		const LightContext * GetLightContext() const { return m_LightContext; }
		void SetLightContext(LightContext * context) { m_LightContext = context; }

		void Clear();

	private:
		// collected render context in levels
		std::vector<RenderContext *> m_RenderContexts;

		// camera context
		CameraContext * m_CameraContext = nullptr;
		// light context
		LightContext * m_LightContext = nullptr;
	};
}