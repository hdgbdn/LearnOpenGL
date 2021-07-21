#ifndef _OPERATION_VEC_H_
#define _OPERATION_VEC_H_

#include <vector>
#include <initializer_list>
#include "Operation.h"

namespace hdgbdn
{
	class OperationVec
	{
	public:
		OperationVec() = default;
		OperationVec(const Operation&);
		OperationVec(const std::initializer_list<Operation>&);
		void push_back(const Operation&);
		void operator()();
	private:
		std::vector<Operation> vec_op;
	};
}

#endif

