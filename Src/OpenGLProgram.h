#pragma once

#include <IProgram.h>
#include <glad/glad.h>

namespace Catherine
{
	class GLProgram : public IProgram
	{
	public:
		GLProgram();
		~GLProgram();

		virtual void AttachShader(const char * vertex, const char * fragment) override;
		virtual bool Compile() override;
		virtual bool Link() override;
		virtual void Use() override;

	private:
		GLuint CreateShader(GLenum param_Type, const char * param_FileName, const char * param_Default);

		bool CheckCompileStatus(GLuint param_Shader);
		bool CheckLinkStatus(GLuint param_Program);

	private:
		GLuint m_Program = 0;

		GLuint m_VertexShader = 0;
		GLuint m_FragmentShader = 0;
	};
}
