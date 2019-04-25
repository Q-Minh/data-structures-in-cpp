#pragma once

#include <exception>
#include <utility>

namespace data_structures_cpp {

template <typename T, std::size_t default_capacity = 100>
class array_stack
{
public:
	using value_type = T;

	explicit array_stack(std::size_t cap = default_capacity)
		: stack_(new T[cap]), capacity_(cap), top_(-1)
	{ }

	std::size_t size() const
	{
		return top_ + 1;
	}

	bool empty() const
	{
		return top_ < 0;
	}

	const T& top() const
	{
		if (empty()) std::runtime_error("empty stack");
		return stack_[top_];
	}

	template <typename U>
	void push(U&& elem)
	{
		if (size() == capacity_) throw std::runtime_error("stack full");
		stack_[++top_] = std::forward<U>(elem);
	}

	void pop()
	{
		if (empty()) throw std::runtime_error("stack empty");
		--top_;
	}

private:
	T* stack_;
	std::size_t capacity_;
	int top_;
};

}