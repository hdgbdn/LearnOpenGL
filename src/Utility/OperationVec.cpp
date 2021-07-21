#include "OperationVec.h"

using namespace hdgbdn;

OperationVec::OperationVec(const Operation& rhs): vec_op({rhs}) {}

OperationVec::OperationVec(const std::initializer_list<Operation>& rhs): vec_op(rhs) {}

void OperationVec::push_back(const Operation& op)
{
	vec_op.push_back(op);
}


void OperationVec::operator()()
{
	for (auto op : vec_op)
	{
		op();
	}
}
