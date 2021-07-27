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

void hdgbdn::glfwCursorPosCbHelper(GLFWwindow* w, double posX, double posY)
{
	Input* pInput = Input::winInputMap[w];
	if(pInput != nullptr)
	{
		pInput->cursorChanged = true;
		const double lastX = pInput->lastCursorX;
		const double lastY = pInput->lastCursorY;
		pInput->lastCursorX = posX;
		pInput->lastCursorY = posY;
		pInput->cursorDeltaX = posX - lastX;
		pInput->cursorDeltaY = posY - lastY;
	}
}

void hdgbdn::glfwMouseButtonCbHelper(GLFWwindow* w, int button, int action, int mod)
{
	Input* pInput = Input::winInputMap[w];
	if (pInput != nullptr)
	{
		if (button >= 0 && button < pInput->keyCount)
		{
			if (action == GLFW_PRESS)
				pInput->keyDown[button] = true;
			if (action == GLFW_RELEASE)
			{
				for(int i = 0; i < pInput->keyRelease.size(); ++i) pInput->keyRelease[button] = false;
				// only previous is down and current is released, can trigger release
				if (pInput->keyDown[button] == true)
					pInput->keyRelease[button] = true;
				else
					pInput->keyRelease[button] = false;
				
				pInput->keyDown[button] = false;
			}
		}
	}
}

Input::Input(Window& win) :
	win(win.get()), lastFrame(0.0), delta(0.0), keyCount(512),
	lastCursorX(), lastCursorY(), cursorDeltaX(), cursorDeltaY(), cursorChanged(false),
	keyDownOp(), keyReleaseOp(), keyDown(keyCount, false), keyRelease(keyCount, false), vecCursorPosCb()
{
	if (winInputMap.find(win) != winInputMap.end()) throw(invalid_argument("already have a Input with this window"));
	winInputMap.insert({win.get(), this});
	glfwSetKeyCallback(win, glfwKeyCbHelper);
	glfwSetCursorPosCallback(win, glfwCursorPosCbHelper);
	glfwSetMouseButtonCallback(win, glfwMouseButtonCbHelper);
}

double Input::GetDelta() const
{
	return delta;
}

glm::vec2 Input::GetCursorPos()
{
	return glm::vec2(lastCursorX, lastCursorY);
}


glm::vec2 Input::GetCursorDelta()
{
	return glm::vec2(cursorDeltaX, cursorDeltaY);
}


void Input::Update()
{
	double newFrame = glfwGetTime();
	delta = newFrame - lastFrame;
	lastFrame = newFrame;
	
	// invoke key call back every frame
	for(int i = 0; i < keyDown.size(); ++i)
	{
		if (IsKeyDown(i) && (keyDownOp.find(i) != keyDownOp.end())) keyDownOp[i]();
		if (IsKeyRelease(i) && (keyReleaseOp.find(i) != keyReleaseOp.end())) 
		{
			keyRelease[i] = false;
			keyReleaseOp[i]();
		}
	}
	
	// only invoke cursor position call back when position changed
	if(cursorChanged)
	{
		cursorChanged = false;
		for(auto cb : vecCursorPosCb)
		{
			cb(lastCursorX, lastCursorY, cursorDeltaX, cursorDeltaY);
		}
	}
	
}

void Input::ShowCursor()
{
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Input::HideCursor()
{
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}


void Input::DisableCursor()
{
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}


void Input::SetKeyDownCb(int key, Operation op)
{
	keyDownOp[key] = op;
}

void Input::SetKeyReleaseCb(int key, Operation op)
{
	keyReleaseOp[key] = op;
}


void Input::SetCursorPosCb(const CursorPosFunc& func)
{
	vecCursorPosCb.push_back(func);
}

void Input::SetCursorPosCb(CursorPosFunc&& func)
{
	vecCursorPosCb.push_back(std::move(func));
}


void Input::RemoveKeyDownCb(int key)
{
	keyDownOp.erase(key);
}

bool Input::IsKeyDown(int key)
{
	return keyDown[key];
}

bool Input::IsKeyRelease(int key)
{
	return keyRelease[key];
}

Input::~Input()
{
	winInputMap.erase(win);
}



