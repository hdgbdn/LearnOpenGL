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
	click_map[key] = op;
}

void EventMgr::SetKeyPress(int key, Operation* op)
{
	if (nullptr != op)
		SetKeyPress(key, Operation::ToPtr(op));
}

void EventMgr::SetKeyPress(int key, Ptr<Operation> op)
{
	press_map[key] = op;
}

void EventMgr::TrigerEvent(int key, ENVENT_TYPE type)
{
	switch (type)
	{
	case CLICK:
		if (nullptr != click_map[key])
			click_map[key]->Run();
	case PRESSS:
		if (nullptr != press_map[key])
			press_map[key]->Run();
	}
}

