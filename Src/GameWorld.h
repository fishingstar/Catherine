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
		virtual void Render() override;

		virtual const WorldContext * GetWorldContext() const override { return m_WorldContext; }

	private:
		WorldContext * m_WorldContext;

		std::vector<ILevel *> m_Levels;
	};
}