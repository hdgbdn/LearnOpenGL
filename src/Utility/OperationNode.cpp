#include "OperationNode.h"

using namespace hdgbdn;

OperationNode::OperationNode(const Operation& rhs): vec_op({rhs}) {}

OperationNode::OperationNode(const std::initializer_list<Operation>& rhs): vec_op(rhs) {}

void OperationNode::operator()()
{
	for (auto op : vec_op)
	{
		op();
	}
}
