#include <OpenGLDevice.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <const.h>
#include <OpenGLCommon.h>
#include <OpenGLVertexArray.h>
#include <OpenGLVertexBuffer.h>
#include <OpenGLIndexBuffer.h>

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
		GLenum tmp_mode = OpenGLCommon::GetOpenGLFrontFaceMode(mode);
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
		GLenum tmp_mode = OpenGLCommon::GetOpenGLDepthTestMode(mode);
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
		GLenum tmp_mode = OpenGLCommon::GetOpenGLCullFaceMode(mode);
		glCullFace(tmp_mode);
	}

	IVertexArray * OpenGLDevice::CreateVertexArray()
	{
		OpenGLVertexArray * tmp_array = new OpenGLVertexArray();
		return tmp_array;
	}

	IVertexBuffer * OpenGLDevice::CreateVertexBuffer(unsigned int size, unsigned int usage, const void * data, const std::vector<AttributeLayout> & attributes)
	{
		OpenGLVertexBuffer * tmp_buffer = new OpenGLVertexBuffer(size, usage, data, attributes);
		return tmp_buffer;
	}

	IIndexBuffer * OpenGLDevice::CreateIndexBuffer(unsigned int stride, unsigned int size, unsigned int usage, const void * data)
	{
		OpenGLIndexBuffer * tmp_buffer = new OpenGLIndexBuffer(stride, size, usage, data);
		return tmp_buffer;
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