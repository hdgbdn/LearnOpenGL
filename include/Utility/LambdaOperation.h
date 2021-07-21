#ifndef _LAMBDA_OPERATION_H_
#define _LAMBDA_OPERATION_H_

#include <functional>
#include <memory>
#include "Operation.h"
#include "Operation_base.h"

namespace hdgbdn
{
	class LambdaOperation: public Operation_base
	{
		friend class Operation;
	public:
		LambdaOperation(const std::function<void()>&);
		LambdaOperation(std::function<void()>&&);
		~LambdaOperation() override;
	protected:
		void operator()() override;
	private:
		std::function<void()> func;
	};
}

#endif