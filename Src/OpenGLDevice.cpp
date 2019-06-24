#include <OpenGLDevice.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <const.h>

namespace Catherine
{
	GLFWwindow * window = nullptr;

	void framebuffer_size_callback(GLFWwindow * param_Window, int param_width, int param_height)
	{
		glViewport(0, 0, param_width, param_height);
	}

	bool OpenGLDevice::Initialize()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

		window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
		if (window == nullptr)
		{
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		// load procedure address
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return false;
		}

		return true;
	}

	void OpenGLDevice::Uninitialize()
	{
		glfwTerminate();
	}

	bool OpenGLDevice::WindowShouldClose()
	{
		return glfwWindowShouldClose(window);
	}

	void OpenGLDevice::ClearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
	}

	void OpenGLDevice::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLDevice::SetFrontFace(FrontFaceMode mode)
	{
		GLenum tmp_mode = GL_CCW;
		switch (mode)
		{
		case FrontFaceMode::Clockwise:
			tmp_mode = GL_CW;
			break;
		case FrontFaceMode::CounterClockwise:
			tmp_mode = GL_CCW;
			break;
		default:
			tmp_mode = GL_CCW;
			break;
		}
		glFrontFace(tmp_mode);
	}

	void OpenGLDevice::EnableDepthTest(bool enabled)
	{
		if (enabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLDevice::SetDepthTestMode(DepthTestMode mode)
	{
		GLenum tmp_mode = GL_LEQUAL;
		switch (mode)
		{
		case DepthTestMode::Always:
			tmp_mode = GL_ALWAYS;
			break;
		case DepthTestMode::Equal:
			tmp_mode = GL_EQUAL;
			break;
		case DepthTestMode::Greater:
			tmp_mode = GL_GREATER;
			break;
		case DepthTestMode::GreaterEqual:
			tmp_mode = GL_GEQUAL;
			break;
		case DepthTestMode::Less:
			tmp_mode = GL_LESS;
			break;
		case DepthTestMode::LessEqual:
			tmp_mode = GL_LEQUAL;
			break;
		case DepthTestMode::Never:
			tmp_mode = GL_NEVER;
			break;
		case DepthTestMode::NotEqual:
			tmp_mode = GL_NOTEQUAL;
			break;
		default:
			tmp_mode = GL_LEQUAL;
			break;
		}
		glDepthFunc(tmp_mode);
	}

	void OpenGLDevice::EnableCullFace(bool enabled)
	{
		if (enabled)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}

	void OpenGLDevice::SetCullFaceMode(CullFaceMode mode)
	{
		GLenum tmp_mode = GL_BACK;
		switch (mode)
		{
		case CullFaceMode::Back:
			tmp_mode = GL_BACK;
			break;
		case CullFaceMode::Front:
			tmp_mode = GL_FRONT;
			break;
		case CullFaceMode::Both:
			tmp_mode = GL_FRONT_AND_BACK;
			break;
		default:
			tmp_mode = GL_BACK;
			break;
		}
		glCullFace(tmp_mode);
	}

	void OpenGLDevice::OnFrameBegin()
	{
		ProcessInput();
	}

	void OpenGLDevice::OnFrameEnd()
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void OpenGLDevice::ProcessInput()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
}