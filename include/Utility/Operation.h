#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <memory>
#include <functional>
#include "Operation_base.h"
#include "LambdaOperation.h"

namespace hdgbdn
{
	using LambdaFunc = std::function<void()>;
	class Operation
	{
	public:
		Operation(const Operation&) = default;
		Operation(Operation&&) = default;

		Operation& operator=(const Operation&) = default;
		Operation& operator=(Operation&&) = default;

		// TODO: maybe template, use only one function to match all possible types?
		Operation(const LambdaFunc&);
		Operation(LambdaFunc&&);
		virtual void operator()();
		virtual ~Operation();
	private:
		std::shared_ptr<Operation_base> p;
	};
}

#endif