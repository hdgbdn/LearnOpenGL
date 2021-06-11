#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <string>
#include "OpQueue.h"

using namespace std;

namespace Hdgbdn
{
    class Window
    {
    public:
        Window(unsigned int width, unsigned int height, const string& name);
        void Terminate();
        int GetKey(int key);
        GLFWAPI GLFWglproc GetProcAddress(const char* procname);
        void Run(Operation* op);
        void Run(Ptr<Operation>& op);
        GLFWwindow* GetWindow();
    private:
        GLFWwindow *window;
        static void CB_FrameBufferSize(GLFWwindow* window, int width, int height);
        void LoadGL();
    };
}

#endif