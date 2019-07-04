#pragma once

namespace Catherine
{
	class IWorld
	{
	public:
		virtual bool Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
	};
}