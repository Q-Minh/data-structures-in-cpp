#pragma once

#include <exception>
#include <utility>

#include "list/list_tags.h"

namespace data_structures_cpp {

template <typename T, typename tag>
class linked_list_stack
{
public:
	linked_list_stack()
		: n_(0)
	{ }

	std::size_t size() const
	{
		return n_;
	}

	bool empty() const
	{
		return n_ == 0;
	}

	const T& top() const
	{
		if (empty()) throw std::runtime_error("empty stack");
		return list_.front();
	}

	template <typename U>
	void push(U&& elem)
	{
		list_.push_front(std::forward<U>(elem));
		++n_;
	}

	void pop()
	{
		if (empty()) throw std::runtime_error("empty stack");
		list_.pop_front();
		--n_;
	}

private:
	typename detail::list_type<tag>::template type<T> list_;
	int n_;
};

}