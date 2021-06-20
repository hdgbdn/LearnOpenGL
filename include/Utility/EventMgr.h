#ifndef _EVENTMGR_H_
#define _EVENTMGR_H_

#include <functional>
#include "Singleton.h"
#include "Operation.h"
#include "OpQueue.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "unordered_map"

namespace Hdgbdn
{
	using KeyOpMap = std::unordered_map <int, Ptr<Operation>>;
	using MousePosCb = std::function<void(double, double)>;

	enum ENVENT_TYPE
	{
		CLICK,
		PRESSS,
		RELEASE,
	};
	class EventMgr : public Singleton<EventMgr>
	{
	public:
		struct Mouse
		{
			glm::vec2 pos;				// Current position of the mouse or touch event
			glm::vec2 last_pos;			// Previous position of the mouse or touch event
			glm::vec2 delta;			// Delta since last update
			Mouse(): pos(), last_pos(), delta() {}
		};
		
		double current_frame;
		double delta_time;

		Mouse mouse;

		void SetKeyClick(int key, Operation* op);
		void SetKeyClick(int key, Ptr<Operation> op);
		void SetKeyPress(int key, Operation* op);
		void SetKeyPress(int key, Ptr<Operation> op);
		void SetKeyCb(int key, ENVENT_TYPE type, Operation* op);
		void SetMousePosCb(MousePosCb* cb);
		void ResponseGlfwKeyEvent(int key, int action);
		void ProcessMousePos(double x, double y);
		void UpdateFrame(double new_frame);
	protected:
	private:
		KeyOpMap click_func_map;
		KeyOpMap press_func_map;
		KeyOpMap release_func_map;
		Ptr<MousePosCb> ptr_mouse_pos_cb;
		void TrigerKeyEvent(int key, ENVENT_TYPE type);
	};
}

#endif