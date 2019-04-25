#pragma once

#include <list>
#include <memory>

#include "linked_binary_tree_node.h"
#include "binary_tree_position.h"

namespace data_structures_cpp {

template <typename T> class linked_binary_tree;

template <typename T>
class linked_binary_tree_position : binary_tree_position<linked_binary_tree_position, T>
{
public:
	using children_type = std::list<linked_binary_tree_position>;

	explicit linked_binary_tree_position(linked_binary_tree_node<T>* v = nullptr) : v_(v) {}
	
	T& operator*() { return *(v_->value_); }
	T const& operator*() const { return *(v_->value_); }
	T* operator->() const { return v_->value_.get(); }
	bool operator==(linked_binary_tree_position const& rhs) const { return v_ == rhs.v_; }
	linked_binary_tree_position left() const { return linked_binary_tree_position(v_->left_); }
	linked_binary_tree_position right() const { return linked_binary_tree_position(v_->right_); }
	linked_binary_tree_position parent() const { return linked_binary_tree_position(v_->parent_); }

	bool root() const { return v_->parent_ == nullptr; }
	bool external() const { return v_->left_ == nullptr && v_->right_ == nullptr; }
	friend class linked_binary_tree<T>;
private:
	linked_binary_tree_node<T>* v_;
};

}