#include "Window.h"
#include <iostream>

using namespace std;
using namespace hdgbdn;

Window::Window(unsigned w, unsigned h, const string& name):isInit(false), pW(nullptr)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    pW = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
    glfwMakeContextCurrent(pW);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Window::StartRenderLoop(Window& win)
{
	while(!glfwWindowShouldClose(win.pW))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glfwSwapBuffers(win.pW);
		//glfwPollEvents();
	}
}

Window::~Window()
{
    glfwTerminate();
}
