#ifndef _EVENTMGR_H_
#define _EVENTMGR_H_

#include "Singleton.h"
#include "Operation.h"
#include "OpQueue.h"
#include "GLFW/glfw3.h"
#include "unordered_map"

namespace Hdgbdn
{
	using KeyOpMap = std::unordered_map <int, Ptr<Operation>>;

	class EventMgr : public Singleton<EventMgr>
	{
	public:
		enum ENVENT_TYPE
		{
			CLICK,
			PRESSS,
		};
		void SetKeyClick(int key, Operation* op);
		void SetKeyClick(int key, Ptr<Operation> op);
		void SetKeyPress(int key, Operation* op);
		void SetKeyPress(int key, Ptr<Operation> op);
		void TrigerEvent(int key, ENVENT_TYPE type);
	private:
		KeyOpMap click_func_map;
		KeyOpMap press_func_map;
	};
}

#endif