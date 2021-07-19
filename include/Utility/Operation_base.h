#ifndef _OPERATION_BASE_H_
#define _OPERATION_BASE_H_

#include "Operation.h"

namespace hdgbdn {
	class Operation_base
	{
	public:
		virtual void operator()() = 0;
		Operation_base& operator=(const Operation_base&) = delete;
		Operation_base& operator=(Operation_base&&) = delete;
	protected:
		virtual ~Operation_base() {}
	};

}

#endif
