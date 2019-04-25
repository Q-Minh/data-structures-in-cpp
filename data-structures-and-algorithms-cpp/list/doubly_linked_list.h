#pragma once

#include <exception>
#include <utility>
#include <memory>

#include "list_utils.h"

namespace data_structures_cpp {

template <typename T>
class doubly_linked_list
{
public:
	using value_type = T;
	using node_type = doubly_linked_node<T>;

	explicit doubly_linked_list() :
		head_(new doubly_linked_node<T>),
		tail_(new doubly_linked_node<T>)
	{
		head_->next_ = tail_;
		tail_->prev_ = head_;
	}

	~doubly_linked_list()
	{
		while (!this->empty())
		{
			this->pop_front();
		}
		delete head_;
		delete tail_;
	}

	bool empty() const
	{
		return head_->next_ == tail_;
	}

	const T& front() const
	{
		if (this->empty()) throw std::runtime_error("empty list");
		return *(head_->next_->value_ptr_);
	}

	const T& back() const
	{
		if (this->empty()) throw std::runtime_error("empty list");
		return *(tail_->prev_->value_ptr_);
	}

	template <typename U>
	void push_front(U&& value)
	{
		auto node = new doubly_linked_node<T>;
		do_insert(head_->next_, std::forward<U>(value));
	}

	template <typename U>
	void push_back(U&& value)
	{
		do_insert(tail_, std::forward<U>(value));
	}

	void pop_front()
	{
		if (empty()) throw std::runtime_error("empty list");
		do_remove(head_->next_);
	}

	void pop_back()
	{
		if (empty()) throw std::runtime_error("empty list");
		do_remove(tail_->prev_);
	}

protected:
	template <typename U>
	void do_insert(doubly_linked_node<T>* successor, U&& value)
	{
		auto node = new doubly_linked_node<T>;
		*(node->value_ptr_ = std::make_unique<T>()) = std::forward<U>(value);
		node->next_ = successor;
		node->prev_ = successor->prev_;
		successor->prev_->next_ = node;
		successor->prev_ = node;
	}

	void do_remove(doubly_linked_node<T>* node)
	{
		auto predecessor = node->prev_;
		auto successor = node->next_;
		predecessor->next_ = successor;
		successor->prev_ = predecessor;
		delete node;
	}

protected:
	doubly_linked_node<T>* head() const { return head_; }
	doubly_linked_node<T>* tail() const { return tail_; }
private:
	doubly_linked_node<T>* head_;
	doubly_linked_node<T>* tail_;
};

}