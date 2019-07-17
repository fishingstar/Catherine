#include "TextureManager.h"
#include "IDevice.h"
#include "ITexture.h"
#include "LogUtility.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Catherine
{
	extern IDevice * g_Device;

	TextureManager * TextureManager::Instance()
	{
		static TextureManager s_intance;
		return &s_intance;
	}

	ITexture * TextureManager::GetTexture(const std::string & filename)
	{
		if (filename.empty())
		{
			LogWarning("TextureManager::GetTexture : filename is empty");
			return nullptr;
		}

		ITexture * tmp_result = Find(filename);
		if (tmp_result == nullptr)
		{
			tmp_result = LoadFromFile(filename);
		}
		return tmp_result;
	}

	ITexture * TextureManager::Find(const std::string & filename)
	{
		ITexture * tmp_result = nullptr;

		auto iter = m_Textures.find(filename);
		if (iter != m_Textures.end())
		{
			tmp_result = iter->second;
		}

		return tmp_result;
	}

	ITexture * TextureManager::LoadFromFile(const std::string & filename)
	{
		ITexture * tmp_result = nullptr;

		int width;
		int height;
		int channels;
		unsigned char * tmp_data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
		if (tmp_data)
		{
			// TODO : remove test code
			PixelFormat tmp_format = channels == 3 ? PixelFormat::R8G8B8 : PixelFormat::A8R8G8B8;

			tmp_result = g_Device->CreateTexture();
			tmp_result->Initialize(width, height, tmp_format, tmp_data);
			m_Textures.insert(std::make_pair(filename, tmp_result));
		}
		stbi_image_free(tmp_data);

		return tmp_result;
	}
}