#pragma once

namespace Catherine
{
	class ISceneObject;

	class ILevel
	{
	public:
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
	};
}