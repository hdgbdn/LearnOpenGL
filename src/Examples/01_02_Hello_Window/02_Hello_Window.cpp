#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "LambdaOp.h"
#include "OpQueue.h"
#include "EventMgr.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const string APP_NAME = "Hello Window";

using namespace std;
using namespace Hdgbdn;

int main()
{
	cout << APP_NAME << endl;
	Window window(SCR_WIDTH, SCR_HEIGHT, APP_NAME);
	
	auto initOp = new LambdaOp([&]()
		{
			EventMgr::GetInstance()->SetKeyPress(GLFW_KEY_ESCAPE, new LambdaOp([&]()
			{
					window.CloseWindow();
			}));
		}
	, false);
	auto renderOp = new LambdaOp([]()
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		});

	auto endOp = new LambdaOp([&]()
	{
			glfwSwapBuffers(window.GetWindow());
			glfwPollEvents();
	});
	auto opQueue = new OpQueue;
	(*opQueue) << initOp << renderOp << endOp;
	window.Run(opQueue);
	return 0;
}