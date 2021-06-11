#pragma once
#include "Operation.h"
#include <functional>
namespace Hdgbdn
{
	class LambdaOp : public Operation
	{
	public:
		LambdaOp(const std::function<void()>& op = []() {}, bool isHold = true);
		void SetOp(const std::function<void()> &op);

		virtual void Run() override;
	protected:
		virtual ~LambdaOp();
		std::function<void()> op;
	private:
		LambdaOp(const LambdaOp&) = delete;
		LambdaOp& operator=(const LambdaOp&) = delete;
	};
}

