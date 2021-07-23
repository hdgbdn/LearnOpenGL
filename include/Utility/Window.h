#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <string>
#include "GLFW/glfw3.h"
#include "Input.h"
#include "OperationVec.h"

using namespace std;

namespace hdgbdn
{
    class Window
    {
        friend Window& operator<<(const Window&, const Operation&);
    public:
        Window(unsigned int w = 1280, unsigned int h = 720, const string& name = "Untitled Window");
        Window(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(const Window&) = delete;
        Window& operator=(Window&&) = delete;

        static void StartRenderLoop(Window&);

        void PushPreRenderOperation(const Operation&);
        void PushRenderOperation(const Operation&);
        void PushPostRenderOperation(const Operation&);

        void Close() const;
    	
        operator GLFWwindow* ();
        GLFWwindow* get() const;
        ~Window();
    private:
        bool isInit;
        GLFWwindow* pW;

        OperationVec preRenderOpVec;
        OperationVec renderOpVec;
        OperationVec postRenderOpVec;
    };
}

#endif