#pragma once

#include "Operation.h"
#include <list>

namespace Hdgbdn
{
	class OpQueue : public Operation
	{
	public:
		OpQueue(bool isHold = true);
		OpQueue& operator <<(const Ptr<Operation>& op);
		OpQueue& operator <<(Operation* op);
		void Push(Ptr<Operation>& op);
		void Push(Operation* op);
		size_t Size() const;

		virtual void Run() override;
	protected:
		virtual ~OpQueue();
		std::list<Ptr<Operation>> opList;
	private:
		OpQueue(const OpQueue&) = delete;
		OpQueue operator=(const OpQueue&) = delete;
	};
}