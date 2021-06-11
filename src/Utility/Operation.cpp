#include "Operation.h"

#include <iostream>

using namespace Hdgbdn;
using namespace std;

Operation::Operation(bool isHold) : isHold(isHold) {};

Operation::~Operation() { std::cout << "INFO: Delete Operation" << std::endl; }

void Operation::ProtectDelete(Operation* op) { delete op; }

bool Operation::IsHold() { return isHold; }

void Operation::SetIsHold(bool isHold) { this->isHold = isHold; }

void Operation::operator()() { Run(); }


