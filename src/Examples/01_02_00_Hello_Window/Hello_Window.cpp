#include <iostream>
#include "Window.h"
#include "Input.h"
#include "Operation.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const string APP_NAME = "Hello Window";

using namespace std;
using namespace hdgbdn;

int main()
{
	cout << APP_NAME << endl;
	Window w(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	w.PushRenderOperation(Operation([&]
		{
			glfwPollEvents();
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(w);
		}));
	Window::StartRenderLoop(w);
	return 0;
}