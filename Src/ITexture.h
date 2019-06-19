#pragma once

namespace Catherine
{
	class ITexture
	{
	public:
		virtual void LoadFromFile(const char * param_Path) = 0;
		virtual void Use(unsigned int slot) = 0;
	};
}
