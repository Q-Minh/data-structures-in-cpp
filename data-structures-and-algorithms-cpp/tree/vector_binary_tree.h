#pragma once

#include <vector>
#include <cstddef>

#include "vector_binary_tree_node.h"
#include "vector_binary_tree_position.h"

namespace data_structures_cpp {

template <typename T>
class vector_binary_tree
{
	using children_t = typename vector_binary_tree_position<T>::children_type;
	using position_t = vector_binary_tree_position<T>;
	using node_t = typename position_t::node_t;
public:
	explicit vector_binary_tree() = default;

	std::size_t size() const { return size_; }
	bool empty() const { return size_ == 0; }
	position_t root() 
	{ 
		if (size_ == 0) return position_t(0, tree_);
		position_t root(1, tree_);
		return root;
	}

	void add_root()
	{
		position_t root(1, tree_);
		tree_.resize(2); // vector-based approach must have 2 elements, as root starts at index 1
		tree_[root.v_].empty_ = false;
		size_ = 1;
	}

	void expand_external(position_t const& p)
	{
		tree_.resize(p.right().v_ + 1);
		if (!p.external()) throw std::runtime_error("vertice is not external");

		tree_[p.left().v_].empty_ = false;
		tree_[p.right().v_].empty_ = false;
		size_ += 2;
	}

	position_t remove_above_external(position_t const& below)
	{
		if (!below.external()) throw std::runtime_error("vertice is not external");

		position_t above = below.parent();
		position_t sibling = below.v_ == above.left().v_ ? above.right() : above.left();
		std::size_t v = sibling.v_;
		if (above.v_ == root().v_)
		{
			tree_[1].value_ = *sibling;
			sibling.v_ = 1;
		}
		else
		{
			position_t grandparent = above.parent();
			if (above.v_ == grandparent.left().v_)
			{
				tree_[grandparent.left().v_].value_ = *sibling;
				sibling.v_ = grandparent.left().v_;
			}
			else
			{
				tree_[grandparent.right().v_].value_ = *sibling;
				sibling.v_ = grandparent.right().v_;
			}
		}
		tree_[below.v_].empty_ = true;
		tree_[v].empty_ = true;
		size_ -= 2;
		return sibling;
	}

	children_t positions()
	{
		children_t list{};
		preorder(root(), list);
		return list;
	}

protected:
	void preorder(position_t pos, children_t& positions) const
	{
		positions.push_back(pos);
		if (pos.left().v_ < tree_.size() && !(tree_[pos.left().v_].empty_))		
			preorder(pos.left(), positions);
		if (pos.right().v_ < tree_.size() && !(tree_[pos.right().v_].empty_))	
			preorder(pos.right(), positions);
	}

private:
	std::vector<node_t> tree_{};
	std::size_t size_{ 0 };
};

}