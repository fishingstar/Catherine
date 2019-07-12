#pragma once

#include <ITexture.h>
#include <glad/glad.h>

namespace Catherine
{
	class OpenGLTexture : public ITexture
	{
	public:
		virtual void LoadFromFile(const char * param_Path) override;
		virtual void Use(unsigned int slot) override;

	private:
		unsigned int m_Texture = 0;
	};
}
