#pragma once
#include <memory>

namespace Hdgbdn
{
	template<typename T>
	using Ptr = std::shared_ptr<T>;
	class Operation
	{
	public:
		template <typename T>
		static Ptr<T> ToPtr(T* op) {
			return Ptr<T>(op, ProtectDelete);
		}

		bool IsHold();
		void SetIsHold(bool isHold);
		void operator()();
		virtual void Run() = 0;
	protected:
		Operation(bool isHold = true);
		static void ProtectDelete(Operation* op);

		/// <summary>
		/// virtual Destructor, for a base pointer to destroy a derived object
		/// </summary>
		virtual ~Operation();
		bool isHold;
	private:
		/// <summary>
		/// prevent copy construct
		/// </summary>
		/// <param name=""></param>
		Operation(const Operation&) = delete;
		/// <summary>
		/// prevent assign construct
		/// </summary>
		/// <param name=""></param>
		/// <returns></returns>
		Operation& operator=(const Operation&) = delete;
	};
}

