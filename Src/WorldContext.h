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
		const std::vector<RenderContext *> & GetRenderContexts() const { return m_RenderContexts; }

		void SetSkyboxRenderContext(RenderContext * context) { m_SkyboxRenderContext = context; }
		RenderContext * GetSkyboxRenderContext() const { return m_SkyboxRenderContext; }

		const CameraContext * GetCameraContext() const { return m_CameraContext; }
		void SetCameraContext(CameraContext * context) { m_CameraContext = context; }

		const LightContext * GetLightContext() const { return m_LightContext; }
		void SetLightContext(LightContext * context) { m_LightContext = context; }

		void Clear();

	private:
		// collected render context in levels
		std::vector<RenderContext *> m_RenderContexts;
		// skybox render context
		RenderContext * m_SkyboxRenderContext;

		// camera context
		CameraContext * m_CameraContext = nullptr;
		// light context
		LightContext * m_LightContext = nullptr;
	};
}