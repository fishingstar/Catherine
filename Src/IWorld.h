#pragma once

namespace Catherine
{
	class IWorld
	{
	public:
		virtual void Update(float deltaTime) = 0;
	};
}