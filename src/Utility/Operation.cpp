#include "Operation.h"

using namespace hdgbdn;

Operation::Operation(LambdaFunc&& rhs)
{
	p = std::make_shared<LambdaOperation>(std::move(rhs));
}

Operation::Operation(const LambdaFunc& rhs)
{
	p = std::make_shared<LambdaOperation>(rhs);
}

void Operation::operator()()
{
	p->operator()();
}

Operation::~Operation() { }

