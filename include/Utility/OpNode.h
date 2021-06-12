#ifndef _OPNODE_H_
#define _OPNODE_H_

#include "OpQueue.h"
#include "LambdaOp.h"

namespace Hdgbdn
{
	class OpNode: public OpQueue
	{
	public:
		OpNode(const Ptr<Operation>& preOp = nullptr, const Ptr<Operation>& postOp = nullptr, bool isHold = true);
		OpNode(const std::function<void()>& preOp = nullptr, const std::function<void()>& postOp = nullptr, bool isHold = true);
		OpNode(Operation* preOp = nullptr, Operation* postOp = nullptr, bool isHold = true);

		void SetPreOp(const Ptr<Operation>& preOp);
		void SetPreOp(Operation* preOp);
		void SetPostOp(const Ptr<Operation>& postOp);
		void SetPostOp(Operation* postOp);
		size_t ChildNum();
		virtual void Run() override;
	protected:
		using OpQueue::Size;
		virtual ~OpNode();

		Ptr<Operation> preOp;
		Ptr<Operation> postOp;
	private:
		OpNode(const OpNode&) = delete;
		OpNode operator=(const OpNode&) = delete;
	};
}

#endif