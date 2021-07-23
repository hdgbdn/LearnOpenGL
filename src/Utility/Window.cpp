#include <iostream>
#include "glad/glad.h"
#include "Window.h"

using namespace std;
using namespace hdgbdn;

Window::Window(unsigned w, unsigned h, const string& name)
		:isInit(false), pW(nullptr), preRenderOpVec(), renderOpVec(), postRenderOpVec()
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
        throw(runtime_error("failed to initialize GLAD"));
    }
    isInit = true;

}

void Window::PushPreRenderOperation(const Operation& op)
{
    preRenderOpVec.push_back(op);
}

void Window::PushRenderOperation(const Operation& op)
{
    renderOpVec.push_back(op);
}


void Window::PushPostRenderOperation(const Operation& op)
{
    postRenderOpVec.push_back(op);
}


void Window::StartRenderLoop(Window& win)
{
    if (!win.isInit)
    {
	    std::cout << "window not init" << endl;
        return;
    }
    win.preRenderOpVec();
	while(!glfwWindowShouldClose(win.pW))
	{
        win.renderOpVec();
	}
    win.postRenderOpVec();
}

Window::operator struct GLFWwindow*()
{
    return pW;
}

GLFWwindow* Window::get() const
{
    return pW;
}

void Window::Close() const
{
    glfwSetWindowShouldClose(pW, true);
}

Window::~Window()
{
    if (!isInit) return;
    glfwTerminate();
}
