#include "LambdaOperation.h"

using namespace hdgbdn;

LambdaOperation::LambdaOperation(const std::function<void()>& rhs):
		p(std::make_shared<std::function<void()>>(rhs)){}

LambdaOperation::LambdaOperation(std::function<void()>&& rhs):
		p(std::make_shared<std::function<void()>>(std::move(rhs))){}


void LambdaOperation::operator()()
{
	p->operator()();
}

LambdaOperation::~LambdaOperation() {}