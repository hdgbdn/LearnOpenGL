#include "Window.h"
#include "EventMgr.h"
#include <iostream>

using namespace std;
using namespace Hdgbdn;

Window::Window(unsigned int width, unsigned int height, const string &name)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *w = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (w == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        exit(1);
    }
    window = w;
    glfwMakeContextCurrent(w);
	glfwSetFramebufferSizeCallback(w, CB_FrameBufferSize);
    LoadGL();
    glViewport(0, 0, width, height);

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scanCode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_RELEASE:
				EventMgr::GetInstance()->TrigerEvent(key, EventMgr::CLICK);
			case GLFW_PRESS:
				EventMgr::GetInstance()->TrigerEvent(key, EventMgr::PRESSS);
			}

		});
}

void Window::CB_FrameBufferSize(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

void Window::LoadGL()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(1);
    }
}

GLFWwindow* Window::GetWindow()
{
    return window;
}


void Window::Run(Operation* op)
{
    Run(Operation::ToPtr(op));
}

void Window::Run(Ptr<Operation>& op)
{
    if (window == nullptr) return;
    bool loop = op != nullptr;
	while(!glfwWindowShouldClose(window))
	{
		if(loop)
		{
            op->Run();
            if (!op->IsHold())
                loop = false;
		}
	}
}

void Window::CloseWindow()
{
    glfwSetWindowShouldClose(window, true);
}

