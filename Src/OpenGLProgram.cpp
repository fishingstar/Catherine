#include "OpenGLProgram.h"
#include "LogUtility.h"
#include "FileUtility.h"
#include "glm/gtc/type_ptr.hpp"

namespace Catherine
{
	const char * vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char * fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.1, 0.2, 0.3, 1.0f);\n"
		"}\n\0";

	OpenGLProgram::OpenGLProgram()
	{
		m_Program = glCreateProgram();
	}

	OpenGLProgram::~OpenGLProgram()
	{
		glDeleteProgram(m_Program);
	}

	void OpenGLProgram::AttachShader(const char * vertex, const char * fragment)
	{
		m_VertexShader = CreateShader(GL_VERTEX_SHADER, vertex, vertexShaderSource);
		m_FragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragment, fragmentShaderSource);
	}

	bool OpenGLProgram::Compile()
	{
		glCompileShader(m_VertexShader);
		bool tmp_vertexOK = CheckCompileStatus(m_VertexShader);
		if (!tmp_vertexOK)
		{
			LogError("Vertex Shader Compile Failed...");
			return false;
		}

		glCompileShader(m_FragmentShader);
		bool tmp_fragmentOK = CheckCompileStatus(m_FragmentShader);
		if (!tmp_fragmentOK)
		{
			LogError("Fragment Shader Compile Failed...");
			return false;
		}

		return true;
	}

	bool OpenGLProgram::Link()
	{
		glAttachShader(m_Program, m_VertexShader);
		glAttachShader(m_Program, m_FragmentShader);
		glLinkProgram(m_Program);

		bool tmp_programOK = CheckLinkStatus(m_Program);
		if (!tmp_programOK)
		{
			LogError("Program Link Failed...");
			return false;
		}

		glDeleteShader(m_VertexShader);
		glDeleteShader(m_FragmentShader);
		return true;
	}

	void OpenGLProgram::Use()
	{
		glUseProgram(m_Program);
	}

	void OpenGLProgram::SetBool(const char * key, bool value)
	{
		glUniform1i(glGetUniformLocation(m_Program, key), value);
	}

	void OpenGLProgram::SetInt(const char * key, int value)
	{
		glUniform1i(glGetUniformLocation(m_Program, key), value);
	}

	void OpenGLProgram::SetFloat(const char * key, float value)
	{
		glUniform1f(glGetUniformLocation(m_Program, key), value);
	}

	void OpenGLProgram::SetVec2(const char * key, const glm::vec2 & value)
	{
		glUniform2fv(glGetUniformLocation(m_Program, key), 1, glm::value_ptr(value));
	}

	void OpenGLProgram::SetVec3(const char * key, const glm::vec3 & value)
	{
		glUniform3fv(glGetUniformLocation(m_Program, key), 1, glm::value_ptr(value));
	}

	void OpenGLProgram::SetVec4(const char * key, const glm::vec4 & value)
	{
		glUniform4fv(glGetUniformLocation(m_Program, key), 1, glm::value_ptr(value));
	}

	void OpenGLProgram::SetMat4x4(const char * key, const glm::mat4x4 & value)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_Program, key), 1, GL_FALSE, glm::value_ptr(value));
	}

	unsigned int OpenGLProgram::CreateShader(GLenum param_Type, const char * param_FileName, const char * param_Default)
	{
		const char * tmp_source = nullptr;

		if (param_FileName != nullptr)
		{
			FileUtility::LoadFileContent(param_FileName, (void **)&tmp_source);
		}

		if (tmp_source == nullptr)
		{
			tmp_source = param_Default;
		}

		unsigned int tmp_shader = glCreateShader(param_Type);
		glShaderSource(tmp_shader, 1, &tmp_source, nullptr);

		return tmp_shader;
	}

	bool OpenGLProgram::CheckCompileStatus(unsigned int param_Shader)
	{
		int tmp_result = 0;
		char tmp_log[1024] = { 0 };

		glGetShaderiv(param_Shader, GL_COMPILE_STATUS, &tmp_result);
		if (!tmp_result)
		{
			glGetShaderInfoLog(param_Shader, sizeof(tmp_log), nullptr, tmp_log);
			LogError(tmp_log);
		}

		return tmp_result;
	}

	bool OpenGLProgram::CheckLinkStatus(unsigned int param_Program)
	{
		int tmp_result = 0;
		char tmp_log[1024] = { 0 };

		glGetProgramiv(param_Program, GL_LINK_STATUS, &tmp_result);
		if (!tmp_result)
		{
			glGetProgramInfoLog(param_Program, sizeof(tmp_log), nullptr, tmp_log);
			LogError(tmp_log);
		}

		return tmp_result;
	}
}
