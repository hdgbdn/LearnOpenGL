#include "LambdaOp.h"
#include <iostream>

using namespace Hdgbdn;
using namespace std;

LambdaOp::LambdaOp(const std::function<void()>& op, bool isHold): op(op), Operation(isHold) {}

LambdaOp::~LambdaOp() { std::cout << "INFO: Delete LambdaOp" << std::endl; }

void LambdaOp::SetOp(const std::function<void()>& op)
{
	this->op = op;
}

void LambdaOp::Run()
{
	if (op == nullptr)
		isHold = false;
	else
		op();
}