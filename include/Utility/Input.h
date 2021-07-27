#ifndef _INPUT_H_
#define _INPUT_H_

#include <unordered_map>
#include <vector>
#include "GLFW/glfw3.h"
#include "Operation.h"
#include "Window.h"
#include "glm/glm.hpp"

namespace hdgbdn
{
	class Window;
	class Input
	{
		using CursorPosFunc = std::function<void(double, double, double, double)>;
		friend void glfwKeyCbHelper(GLFWwindow*, int, int, int, int);
		friend void glfwCursorPosCbHelper(GLFWwindow*, double, double);
		friend void glfwMouseButtonCbHelper(GLFWwindow*, int, int, int);
	public:
		Input(Window&);
		~Input();

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		
		void SetKeyDownCb(int key, Operation);
		void SetKeyReleaseCb(int key, Operation);
		void RemoveKeyDownCb(int key);
		void SetCursorPosCb(CursorPosFunc&&);
		void SetCursorPosCb(const CursorPosFunc&);
		void Update();
		double GetDelta() const;
		glm::vec2 GetCursorPos();
		glm::vec2 GetCursorDelta();

		void ShowCursor();
		void HideCursor();
		void DisableCursor();
	private:
		GLFWwindow* win;
		double lastFrame;
		double delta;
		const int keyCount;
		double lastCursorX;
		double lastCursorY;
		double cursorDeltaX;
		double cursorDeltaY;
		bool cursorChanged;
		
		std::unordered_map<int, Operation> keyDownOp;
		std::unordered_map<int, Operation> keyReleaseOp;
		std::vector<bool> keyDown;
		std::vector<bool> keyRelease;
		std::vector<CursorPosFunc> vecCursorPosCb;
		bool IsKeyDown(int);
		bool IsKeyRelease(int);
		static std::unordered_map<GLFWwindow*, Input*> winInputMap;
	};

}
#endif