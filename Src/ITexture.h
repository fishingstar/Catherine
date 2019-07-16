#pragma once

namespace Catherine
{
	class ITexture
	{
	public:
		virtual bool Initialize(int width, int height, int channel, void * data = nullptr) = 0;
		virtual void Uninitialize() = 0;
		virtual void Use(unsigned int slot) = 0;
	};
}
