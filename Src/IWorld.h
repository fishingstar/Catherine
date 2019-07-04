#pragma once

namespace Catherine
{
	class WorldContext;

	class IWorld
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Update(float deltaTime) = 0;

		virtual void PreRender() = 0;
		virtual void Render() = 0;
		virtual void PostRender() = 0;

		virtual const WorldContext * GetWorldContext() const = 0;
	};
}