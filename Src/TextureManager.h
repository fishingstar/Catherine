#pragma once

#include <string>
#include <unordered_map>

namespace Catherine
{
	class ITexture;

	class TextureManager
	{
	public:
		static TextureManager * Instance();

		ITexture * GetTexture(const std::string & filename);

	private:
		TextureManager() { }

		ITexture * Find(const std::string & filename);
		ITexture * LoadFromFile(const std::string & filename);

	private:
		std::unordered_map<std::string, ITexture *> m_Textures;
	};
}