#include <stdexcept>
#include "Input.h"
#include "Window.h"

using namespace hdgbdn;

std::unordered_map<GLFWwindow*, Input*> Input::winInputMap = std::unordered_map<GLFWwindow*, Input*>();

void hdgbdn::glfwKeyCbHelper(GLFWwindow* w, int key, int scancode, int action, int mods)
{
	Input* pInput = Input::winInputMap[w];
	if(pInput != nullptr)
	{
		if (key >= 0 && key < pInput->keyCount)
		{
			if (action == GLFW_PRESS)
				pInput->keyDown[key] = true;
			if (action == GLFW_RELEASE)
				pInput->keyDown[key] = false;
		}
	}
}

Input::Input(Window& win):win(win.get()) ,lastFrame(0.0), delta(0.0), keyDownOp(), keyPressOp(), keyDown(keyCount, false)
{
	if (winInputMap.find(win) != winInputMap.end()) throw(invalid_argument("already have a Input with this window"));
	winInputMap.insert({win.get(), this});
	glfwSetKeyCallback(win, glfwKeyCbHelper);
}

double Input::GetDelta() const
{
	return delta;
}

void Input::Update()
{
	double newFrame = glfwGetTime();
	delta = newFrame - lastFrame;
	for(int i = 0; i < keyDown.size(); ++i)
	{
		if (IsKeyDown(i) && (keyDownOp.find(i) != keyDownOp.end())) keyDownOp[i]();
	}
}

void Input::SetKeyDownCb(int key, Operation op)
{
	keyDownOp[key] = op;
}

void Input::RemoveKeyDownCb(int key)
{
	keyDownOp.erase(key);
}

bool Input::IsKeyDown(int key)
{
	return keyDown[key];
}

Input::~Input()
{
	winInputMap.erase(win);
}



