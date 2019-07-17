#pragma once

#include <vector>
#include "LightContext.h"

namespace Catherine
{
	class SceneObject;

	class LightManager
	{
	public:
		LightManager();
		~LightManager();

		void Register(SceneObject * obj);
		void Unregister(SceneObject * obj);

		LightContext * GetLightContext();

	private:
		std::vector<SceneObject *> GetDirectionalLights() const;
		std::vector<SceneObject *> GetSpotLights() const;
		std::vector<SceneObject *> GetPointLights() const;
		std::vector<SceneObject *> GetLightsByType(LightType type) const;

	private:
		LightContext * m_LightContext;

		std::vector<SceneObject *> m_Lights;
	};
}