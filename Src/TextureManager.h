#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace Catherine
{
	class ITexture;

	class TextureManager
	{
	public:
		static TextureManager * Instance();

		ITexture * GetTexture(const std::string & filename);
		ITexture * GetCubeTexture(const std::vector<std::string> & filename);

	private:
		TextureManager() { }

		ITexture * Find(const std::string & filename);
		ITexture * LoadFromFile(const std::string & filename);
		ITexture * LoadFromCubeFile(const std::vector<std::string> & filename);

		std::string GetCubeTextureKey(const std::vector<std::string> & filename) const;

	private:
		std::unordered_map<std::string, ITexture *> m_Textures;
	};
}