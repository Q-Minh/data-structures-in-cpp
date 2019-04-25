#pragma once

#include <exception>
#include <utility>

#include "queue/double_ended_queue.h"

namespace data_structures_cpp {

template <typename T>
class double_ended_queue_stack
{
public:
	using value_type = T;

	explicit double_ended_queue_stack() = default;

	std::size_t size() const
	{
		return deque_.size();
	}

	bool empty() const
	{
		return deque_.empty();
	}

	const T& top() const
	{
		if (empty()) throw std::runtime_error("empty stack");
		return deque_.back();
	}

	template <typename U>
	void push(U&& value)
	{
		deque_.push_back(std::forward<U>(value));
	}

	void pop()
	{
		if (empty()) throw std::runtime_error("empty stack");
		deque_.pop_back();
	}

private:
	double_ended_queue<T> deque_;
};

}