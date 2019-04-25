#pragma once

#include <exception>
#include <utility>
#include <memory>

#include "list_utils.h"

namespace data_structures_cpp {

template <typename T>
class singly_linked_list
{
public:
	using value_type = T;

	explicit singly_linked_list() : head_(nullptr) {}
	
	~singly_linked_list()
	{
		while (!this->empty()) this->pop_front();
	}

	bool empty() const
	{
		return head_ == nullptr;
	}

	const T& front() const
	{
		if (empty()) throw std::runtime_error("empty list");
		return *(head_->value_ptr_);
	}

	template <typename U>
	void push_front(U&& elem)
	{
		auto node = new singly_linked_node<T>;
		node->next_ = head_;
		*(node->value_ptr_ = std::make_unique<T>()) = std::forward<U>(elem);
		head_ = node;
	}

	void pop_front()
	{
		if (empty()) throw std::runtime_error("empty list");
		auto node_to_remove = head_;
		head_ = node_to_remove->next_;
		delete node_to_remove;
	}

private:
	singly_linked_node<T>* head_;
};

}