#include "OpenGLDevice.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "DeviceConst.h"
#include "OpenGLCommon.h"
#include "OpenGLProgram.h"
#include "OpenGLTexture.h"
#include "OpenGLCubeTexture.h"
#include "OpenGLVertexArray.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLIndexBuffer.h"
#include "OpenGLRenderTarget.h"

namespace Catherine
{
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

		m_Window = glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, DEFAULT_WINDOW_TITLE, nullptr, nullptr);
		if (m_Window == nullptr)
		{
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(m_Window);
		glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

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

	bool OpenGLDevice::Close()
	{
		return glfwWindowShouldClose(m_Window);
	}

	void OpenGLDevice::SetViewPort(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLDevice::SetClearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
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

	void OpenGLDevice::EnableBlend(bool enabled)
	{
		if (enabled)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}

	void OpenGLDevice::SetBlendEquation(BlendEquation equation)
	{
		GLenum tmp_equation = OpenGLCommon::GetOpenGLBlendEquation(equation);
		glBlendEquation(tmp_equation);
	}

	void OpenGLDevice::SetBlendFunc(BlendFunc src, BlendFunc dst, BlendFunc src_alpha, BlendFunc dst_alpha)
	{
		GLenum tmp_src = OpenGLCommon::GetOpenGLBlendFunc(src);
		GLenum tmp_dst = OpenGLCommon::GetOpenGLBlendFunc(dst);
		GLenum tmp_src_alpha = OpenGLCommon::GetOpenGLBlendFunc(src_alpha);
		GLenum tmp_dst_alpha = OpenGLCommon::GetOpenGLBlendFunc(dst_alpha);
		glBlendFuncSeparate(tmp_src, tmp_dst, tmp_src_alpha, tmp_dst_alpha);
	}

	IProgram * OpenGLDevice::CreateProgram()
	{
		OpenGLProgram * tmp_program = new OpenGLProgram();
		return tmp_program;
	}

	ITexture * OpenGLDevice::CreateTexture()
	{
		OpenGLTexture * tmp_texture = new OpenGLTexture();
		return tmp_texture;
	}

	ITexture * OpenGLDevice::CreateCubeTexture()
	{
		OpenGLCubeTexture * tmp_texture = new OpenGLCubeTexture();
		return tmp_texture;
	}

	IRenderTarget * OpenGLDevice::CreateRenderTarget()
	{
		OpenGLRenderTarget * tmp_rt = new OpenGLRenderTarget();
		return tmp_rt;
	}

	IVertexArray * OpenGLDevice::CreateVertexArray()
	{
		OpenGLVertexArray * tmp_array = new OpenGLVertexArray();
		return tmp_array;
	}

	IVertexBuffer * OpenGLDevice::CreateVertexBuffer(size_t size, Usage usage, const void * data, const std::vector<AttributeLayout> & attributes)
	{
		OpenGLVertexBuffer * tmp_buffer = new OpenGLVertexBuffer(size, usage);
		tmp_buffer->Initialize(data);
		tmp_buffer->SetAttributeLayout(attributes);
		return tmp_buffer;
	}

	IIndexBuffer * OpenGLDevice::CreateIndexBuffer(uint8_t stride, size_t size, Usage usage, const void * data)
	{
		OpenGLIndexBuffer * tmp_buffer = new OpenGLIndexBuffer(stride, size, usage);
		tmp_buffer->Initialize(data);
		return tmp_buffer;
	}

	void OpenGLDevice::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLDevice::DrawElement(DrawMode mode, size_t count, ValueType type, size_t offset)
	{
		GLenum tmp_drawMode = OpenGLCommon::GetOpenGLDrawMode(mode);
		GLenum tmp_valueType = OpenGLCommon::GetOpenGLType(type);
		glDrawElements(tmp_drawMode, (GLsizei)count, tmp_valueType, (void *)offset);
	}

	void OpenGLDevice::BlitFrameBuffer()
	{
		glBlitFramebuffer(0, 0, 1, 1, 0, 0, 1, 1, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLDevice::OnFrameBegin()
	{
		// dispatch input event
		ProcessInput();
	}

	void OpenGLDevice::OnFrameEnd()
	{
		// swap double buffer
		glfwSwapBuffers(m_Window);
		// input event
		glfwPollEvents();
	}

	void OpenGLDevice::ProcessInput()
	{
		if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(m_Window, true);
		}
	}
}