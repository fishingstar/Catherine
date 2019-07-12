#pragma once

#include <vector>
#include <LightContext.h>

namespace Catherine
{
	class ISceneObject;

	class LightManager
	{
	public:
		LightManager();
		~LightManager();

		void Register(ISceneObject * obj);
		void Unregister(ISceneObject * obj);

		LightContext * GetLightContext();

	private:
		std::vector<ISceneObject *> GetDirectionalLights() const;
		std::vector<ISceneObject *> GetSpotLights() const;
		std::vector<ISceneObject *> GetPointLights() const;
		std::vector<ISceneObject *> GetLightsByType(LightType type) const;

	private:
		LightContext * m_LightContext;

		std::vector<ISceneObject *> m_Lights;
	};
}