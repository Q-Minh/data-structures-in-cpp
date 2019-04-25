#pragma once

#include <exception>
#include <utility>
#include <memory>
#include <cstddef>

#include "list_utils.h"

namespace data_structures_cpp {

template <typename T>
class circular_linked_list
{
public:
	explicit circular_linked_list() : cursor_(nullptr), size_(0) {}

	~circular_linked_list()
	{
		while (!empty()) pop_front();
	}

	std::size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return cursor_ == nullptr;
	}

	const T& front() const
	{
		if (empty()) throw std::runtime_error("empty list");
		return *(cursor_->next_->value_ptr_);
	}

	const T& back() const
	{
		if (empty()) throw std::runtime_error("empty list");
		return *(cursor_->value_ptr_);
	}

	void advance()
	{
		if (empty()) throw std::runtime_error("empty list");
		cursor_ = cursor_->next_;
	}

	template <typename U>
	void push_front(U&& value)
	{
		auto node = new singly_linked_node<T>();
		*(node->value_ptr_ = std::make_unique<T>()) = std::forward<U>(value);
		if (cursor_ == nullptr)
		{
			node->next_ = node;
			cursor_ = node;
		}
		else
		{
			node->next_ = cursor_->next_;
			cursor_->next_ = node;
		}
		++size_;
	}

	void pop_front()
	{
		if (empty()) throw std::runtime_error("empty list");
		auto old = cursor_->next_;
		if (cursor_ == old)
		{
			cursor_ = nullptr;
		}
		else
		{
			cursor_->next_ = old->next_;
		}
		delete old;
		--size_;
	}
private:
	singly_linked_node<T>* cursor_;
	std::size_t size_;
};

}