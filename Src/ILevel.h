#pragma once

namespace Catherine
{
	class ISceneObject;
	class WorldContext;

	class ILevel
	{
	public:
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render(WorldContext * context) = 0;
	};
}