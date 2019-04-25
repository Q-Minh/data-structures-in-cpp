#pragma once

#include <utility>

#include "list/doubly_linked_list.h"

namespace data_structures_cpp {

template <typename T>
class double_ended_queue
{
public:
	using value_type = T;

	explicit double_ended_queue() = default;
	
	std::size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return list_.empty();
	}

	template <typename U>
	void push_front(U&& value)
	{
		list_.push_front(std::forward<U>(value));
		++size_;
	}

	template <typename U>
	void push_back(U&& value)
	{
		list_.push_back(std::forward<U>(value));
		++size_;
	}

	const T& front() const
	{
		return list_.front();
	}

	const T& back() const
	{
		return list_.back();
	}

	void pop_front()
	{
		list_.pop_front();
		--size_;
	}

	void pop_back()
	{
		list_.pop_back();
		--size_;
	}

private:
	doubly_linked_list<T> list_;
	int size_{ 0 };
};

}