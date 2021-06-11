#include "OpQueue.h"
#include <iostream>
#include <vector>

using namespace Hdgbdn;
using namespace std;

OpQueue::OpQueue(bool isHold): Operation(isHold) {}
OpQueue::~OpQueue() { cout << "INFO: Delete LambdaOp" << endl; }

OpQueue& OpQueue::operator<<(const Ptr<Operation>& op)
{
	if (op != nullptr)
		opList.push_back(op);
	return *this;
}

OpQueue& OpQueue::operator<<(Operation* op)
{
	if (op != nullptr)
		opList.push_back(Operation::ToPtr(op));
	return *this;
}

void OpQueue::Push(Ptr<Operation>& op)
{
	if (op != nullptr)
		opList.push_back(op);
}


void OpQueue::Push(Operation* op)
{
	if (op != nullptr)
		opList.push_back(Operation::ToPtr(op));
}

size_t OpQueue::Size() const
{
	return opList.size();
}

void OpQueue::Run()
{
	vector<list<Ptr<Operation>>::const_iterator> removeIt;
	for(auto it = opList.cbegin(); it != opList.cend(); it++)
	{
		(*it)->Run();
		if (!(*it)->IsHold())
			removeIt.push_back(it);
	}
	for (auto i : removeIt)
		opList.erase(i);
}