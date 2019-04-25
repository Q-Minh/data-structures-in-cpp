#pragma once

#include <vector>
#include <list>
#include <exception>
#include <cstddef>

#include "vector_binary_tree_node.h"
#include "binary_tree_position.h"

namespace data_structures_cpp {

template <typename T> class vector_binary_tree;

template <typename T>
class vector_binary_tree_position : binary_tree_position<vector_binary_tree_position, T>
{
public:
	using children_type = std::list<vector_binary_tree_position>;
	using node_t = vector_binary_tree_node<T>;

	friend class vector_binary_tree<T>;
	
	explicit vector_binary_tree_position(std::size_t v, std::vector<node_t>& tree)
		: v_(v), tree_(tree)
	{
		if (v <= 0) throw std::runtime_error("invalid node reference");
	}

	vector_binary_tree_position(vector_binary_tree_position const& rhs)
		: v_(rhs.v_), tree_(rhs.tree_)
	{}

	T& operator*() { return tree_[v_].value_; }
	T const& operator*() const { return tree_[v_].value_; }

	vector_binary_tree_position left() const 
	{ 
		return vector_binary_tree_position(2 * v_, tree_); 
	}
	vector_binary_tree_position right() const 
	{ 
		return vector_binary_tree_position(2 * v_ + 1, tree_); 
	}
	vector_binary_tree_position parent() const 
	{ 
		return vector_binary_tree_position(v_ / 2, tree_); 
	}

	bool root() const { return v_ == 1; }
	bool external() const 
	{
		tree_.resize((2 * v_ + 1) + 1);
		return tree_[2 * v_].empty_ && tree_[2 * v_ + 1].empty_; 
	}
private:
	std::size_t v_;
	std::vector<node_t>& tree_;
};

}