#ifndef _OPERATION_NOED_H_
#define _OPERATION_NOED_H_

#include <vector>
#include <initializer_list>
#include "Operation.h"

namespace hdgbdn
{
	class OperationNode
	{
	public:
		OperationNode(const Operation&);
		OperationNode(const std::initializer_list<Operation>&);
		void operator()();
	private:
		std::vector<Operation> vec_op;
	};
}

#endif

