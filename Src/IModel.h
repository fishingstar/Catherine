#pragma once

namespace Catherine
{
	class WorldContext;

	class IModel
	{
	public:
		virtual void LoadFromFile(const char * path) = 0;
		virtual void Render(WorldContext * context) = 0;
	};
}