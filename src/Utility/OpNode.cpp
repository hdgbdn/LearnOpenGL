#include "OpNode.h"
#include <iostream>

using namespace Hdgbdn;
using namespace std;

OpNode::OpNode(const Ptr<Operation>& preOp, const Ptr<Operation>& postOp, bool isHold):preOp(preOp), postOp(postOp), OpQueue(isHold){}

OpNode::OpNode(Operation* preOp, Operation* postOp, bool isHold): OpQueue(isHold)
{
	this->preOp = preOp == nullptr ? nullptr : Operation::ToPtr(preOp);
	this->postOp = postOp == nullptr ? nullptr : Operation::ToPtr(postOp);
}

OpNode::OpNode(const std::function<void()>& preOp, const std::function<void()>& postOp, bool isHold): OpQueue(isHold)
{
	this->preOp = preOp == nullptr ? nullptr : Operation::ToPtr(new LambdaOp(preOp));
	this->postOp = postOp == nullptr ? nullptr : Operation::ToPtr(new LambdaOp(postOp));
}

OpNode::~OpNode() { std::cout << "INFO: Delete OpNode" << std::endl; }

void OpNode::SetPreOp(const Ptr<Operation>& preOp)
{
	this->preOp = preOp;
}


void OpNode::SetPreOp(Operation* preOp)
{
	SetPreOp(preOp == nullptr ? nullptr : Operation::ToPtr(preOp));
}

void OpNode::SetPostOp(const Ptr<Operation>& postOp)
{
	this->postOp = postOp;
}


void OpNode::SetPostOp(Operation* postOp)
{
	SetPostOp(postOp == nullptr ? nullptr : postOp);
}

size_t OpNode::ChildNum()
{
	return Size();
}

void OpNode::Run()
{
	if (preOp != nullptr) preOp->Run();
	OpQueue::Run();
	if (postOp != nullptr) postOp->Run();
}
