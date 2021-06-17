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

void EventMgr::TrigerEvent(int key, ENVENT_TYPE type)
{
	switch (type)
	{
	case CLICK:
		if (click_func_map[key])
			click_func_map[key]->Run();
	case PRESSS:
		if (press_func_map[key])
			press_func_map[key]->Run();
	}
}

