#pragma once

#include <memory>

namespace data_structures_cpp {

template <typename T> class linked_binary_tree;

template <typename T>
struct linked_binary_tree_node
{
	explicit linked_binary_tree_node()
	{
		value_ = std::make_shared<T>();
	}

	std::shared_ptr<T> value_{};
	linked_binary_tree_node* parent_{ nullptr };
	linked_binary_tree_node* left_{ nullptr };
	linked_binary_tree_node* right_{ nullptr };
};

}