#ifndef _INPUT_H_
#define _INPUT_H_

#include <unordered_map>
#include <vector>
#include "GLFW/glfw3.h"
#include "Operation.h"
#include "Window.h"

namespace hdgbdn
{
	class Window;
	class Input
	{
		friend void glfwKeyCbHelper(GLFWwindow*, int, int, int, int);
	public:
		Input(Window&);
		~Input();

		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		
		void SetKeyDownCb(int key, Operation);
		void RemoveKeyDownCb(int key);
		void Update();
		double GetDelta() const;
	private:
		GLFWwindow* win;
		double lastFrame;
		double delta;
		const int keyCount = 512;
		std::unordered_map<int, Operation> keyDownOp;
		std::unordered_map<int, Operation> keyPressOp;
		std::vector<bool> keyDown;
		bool IsKeyDown(int);
		static std::unordered_map<GLFWwindow*, Input*> winInputMap;
	};

}
#endif