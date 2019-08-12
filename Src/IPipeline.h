#pragma once

namespace Catherine
{
	class WorldContext;

	class IPipeline
	{
	public:
		virtual ~IPipeline() { }

		virtual bool Initialize() = 0;
		virtual void Uninitialize() = 0;

		virtual void Render(const WorldContext * context) { }
	};
}