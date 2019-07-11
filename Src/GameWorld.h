#pragma once

#include <IWorld.h>
#include <vector>

namespace Catherine
{
	class ILevel;
	class WorldContext;

	class GameWorld : public IWorld
	{
	public:
		virtual bool Initialize() override;
		virtual void Update(float deltaTime) override;

		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;

		virtual const WorldContext * GetWorldContext() const override { return m_WorldContext; }
		virtual CameraManager * GetCameraManager() const { return m_CameraManager; }

	private:
		WorldContext * m_WorldContext;
		CameraManager * m_CameraManager;

		std::vector<ILevel *> m_Levels;
	};
}