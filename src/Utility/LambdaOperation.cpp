#include "LambdaOperation.h"

using namespace hdgbdn;

LambdaOperation::LambdaOperation(const std::function<void()>& rhs) :
	func(rhs) {}

LambdaOperation::LambdaOperation(std::function<void()>&& rhs) :
	func(std::move(rhs)) {}


void LambdaOperation::operator()()
{
	func();
}

LambdaOperation::~LambdaOperation() {}