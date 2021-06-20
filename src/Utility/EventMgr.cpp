#include "EventMgr.h"

using namespace Hdgbdn;
using namespace std;

void EventMgr::SetKeyClick(int key, Operation* op)
{
	if (nullptr != op)
		SetKeyClick(key, Operation::ToPtr(op));
}

void EventMgr::SetKeyClick(int key, Ptr<Operation> op)
{
	click_func_map[key] = op;
}

void EventMgr::SetKeyPress(int key, Operation* op)
{
	if (nullptr != op)
		SetKeyPress(key, Operation::ToPtr(op));
}

void EventMgr::SetKeyPress(int key, Ptr<Operation> op)
{
	press_func_map[key] = op;
}

void EventMgr::SetKeyCb(int key, ENVENT_TYPE type, Operation* op)
{
	if(op == nullptr) return;
	Ptr<Operation> p_op = Operation::ToPtr(op);
	switch (type)
	{
	case ENVENT_TYPE::CLICK :
		click_func_map[key] = p_op;
		break;
	case ENVENT_TYPE::PRESSS:
		press_func_map[key] = p_op;
		break;
	case ENVENT_TYPE::RELEASE:
		release_func_map[key] = p_op;
		break;
		
	default:
		break;
	}
}

void EventMgr::SetMousePosCb(MousePosCb* cb)
{
	ptr_mouse_pos_cb = Ptr<MousePosCb>(cb);
}

void EventMgr::UpdateFrame(double new_frame)
{
	delta_time = new_frame - current_frame;
	current_frame = new_frame;
}

void EventMgr::ProcessMousePos(double x, double y)
{
	mouse.last_pos = mouse.pos;
	mouse.pos.x = x;
	mouse.pos.y = y;
	mouse.delta = mouse.pos - mouse.last_pos;
	if(ptr_mouse_pos_cb)
		(*ptr_mouse_pos_cb)(x, y);
}

void EventMgr::ResponseGlfwKeyEvent(int key, int action)
{
	switch (action)
	{
	case GLFW_PRESS:
		TrigerKeyEvent(key, ENVENT_TYPE::CLICK);
		TrigerKeyEvent(key, ENVENT_TYPE::PRESSS);
		break;
	
	case GLFW_REPEAT:
		TrigerKeyEvent(key, ENVENT_TYPE::PRESSS);
		break;
		
	case GLFW_RELEASE:
		TrigerKeyEvent(key, ENVENT_TYPE::RELEASE);
		break;
	default:
		break;
	}
}

void EventMgr::TrigerKeyEvent(int key, ENVENT_TYPE type)
{
	switch (type)
	{
	case CLICK:
		if (click_func_map[key])
			click_func_map[key]->Run();
		break;
	case PRESSS:
		if (press_func_map[key])
			press_func_map[key]->Run();
		break;
	case RELEASE:
		if (release_func_map[key])
			release_func_map[key]->Run();
		break;
	}
}

