#include <Material.h>
#include <IDevice.h>
#include <OpenGLProgram.h>
#include <OpenGLTexture.h>

namespace Catherine
{
	extern IDevice * g_Device;

	bool Material::Initialize(const char * param_Config)
	{
		m_Program = new GLProgram();
		m_Program->AttachShader("./res/shader/simple.vs", "./res/shader/simple.fs");
		m_Program->Compile();
		m_Program->Link();

		m_Program->Use();
		m_Program->SetInt("diffuse1", 0);
		m_Program->SetInt("diffuse2", 1);

		m_Texture1 = new GLTexture();
		m_Texture1->LoadFromFile("./res/texture/wall.jpg");

		m_Texture2 = new GLTexture();
		m_Texture2->LoadFromFile("./res/texture/container.jpg");

		return true;
	}

	void Material::SetInt(const char * key, int value)
	{
		m_Program->SetInt(key, value);
	}

	void Material::SetFloat(const char * key, float value)
	{
		m_Program->SetFloat(key, value);
	}

	void Material::SetVec2(const char * key, const glm::vec2 & value)
	{
		m_Program->SetVec2(key, value);
	}

	void Material::SetVec3(const char * key, const glm::vec3 & value)
	{
		m_Program->SetVec3(key, value);
	}

	void Material::SetVec4(const char * key, const glm::vec4 & value)
	{
		m_Program->SetVec4(key, value);
	}

	void Material::SetMat4x4(const char * key, const glm::mat4x4 & value)
	{
		m_Program->SetMat4x4(key, value);
	}

	void Material::Use()
	{
		g_Device->EnableDepthTest(m_DepthTestEnabled);
		g_Device->SetDepthTestMode(m_DepthTestMode);

		g_Device->EnableCullFace(m_CullFaceEnabled);
		g_Device->SetCullFaceMode(m_CullFaceMode);

		m_Texture1->Use(0);
		m_Texture2->Use(1);

		m_Program->Use();
	}
}