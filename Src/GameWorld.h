#pragma once

#include "IWorld.h"
#include <vector>

namespace Catherine
{
	class ILevel;
	class WorldContext;
	class Skybox;

	class GameWorld : public IWorld
	{
	public:
		virtual bool Initialize() override;
		virtual void Uninitialize() override;

		virtual void PreUpdate(float deltaTime) override;
		virtual void Update(float deltaTime) override;
		virtual void PostUpdate(float deltaTime) override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

		virtual const WorldContext * GetWorldContext() const override { return m_WorldContext; }
		virtual CameraManager * GetCameraManager() const { return m_CameraManager; }
		virtual LightManager * GetLightManager() const { return m_LightManager; }

	private:
		WorldContext * m_WorldContext;
		CameraManager * m_CameraManager;
		LightManager * m_LightManager;

		Skybox * m_Skybox;

		std::vector<ILevel *> m_Levels;
	};
}