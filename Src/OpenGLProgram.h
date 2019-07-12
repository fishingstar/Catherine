#pragma once

#include <IProgram.h>
#include <glad/glad.h>

namespace Catherine
{
	class OpenGLProgram : public IProgram
	{
	public:
		OpenGLProgram();
		~OpenGLProgram();

		virtual void AttachShader(const char * vertex, const char * fragment) override;
		virtual bool Compile() override;
		virtual bool Link() override;
		virtual void Use() override;

		virtual void SetBool(const char * key, bool value) override;
		virtual void SetInt(const char * key, int value) override;
		virtual void SetFloat(const char * key, float value) override;
		virtual void SetVec2(const char * key, const glm::vec2 & value) override;
		virtual void SetVec3(const char * key, const glm::vec3 & value) override;
		virtual void SetVec4(const char * key, const glm::vec4 & value) override;
		virtual void SetMat4x4(const char * key, const glm::mat4x4 & value) override;

	private:
		unsigned int CreateShader(GLenum param_Type, const char * param_FileName, const char * param_Default);

		bool CheckCompileStatus(unsigned int param_Shader);
		bool CheckLinkStatus(unsigned int param_Program);

	private:
		unsigned int m_Program = 0;

		unsigned int m_VertexShader = 0;
		unsigned int m_FragmentShader = 0;
	};
}
