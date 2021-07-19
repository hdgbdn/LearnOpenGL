#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <string>

using namespace std;

namespace hdgbdn
{
    class Window
    {
    public:
        Window(unsigned int w = 1280, unsigned int h = 720, const string& name = "Untitled Window");
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        static void StartRenderLoop(Window&);

        void SetFramebufferSizeCallback();
        void SetCursorPosCallback();
        void SetScrollCallback();
        ~Window();
    private:
        bool isInit;
        GLFWwindow* pW;
    };
}

#endif