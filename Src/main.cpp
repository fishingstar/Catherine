#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow * param_Window, int param_Width, int param_Height);
void processInput(GLFWwindow * param_Window);

const unsigned int SRC_WIDTH = 800;
const unsigned int SRC_HEIGHT = 600;
const char * WINDOW_TITLE = "DreamEngine";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	GLFWwindow * tmp_window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
	if (tmp_window == nullptr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(tmp_window);
	glfwSetFramebufferSizeCallback(tmp_window, framebuffer_size_callback);

	// load procedure address
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	while (!glfwWindowShouldClose(tmp_window))
	{
		processInput(tmp_window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(tmp_window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * param_Window, int param_width, int param_height)
{
	glViewport(0, 0, param_width, param_height);
}

void processInput(GLFWwindow * param_Window)
{

}
