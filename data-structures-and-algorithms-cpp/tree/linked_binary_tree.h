#pragma once

#include <list>
#include <stack>
#include <cstddef>
#include <exception>

#include "linked_binary_tree_node.h"
#include "linked_binary_tree_position.h"

namespace data_structures_cpp {

template <typename T>
class linked_binary_tree
{
public:
	using children_t = typename linked_binary_tree_position<T>::children_type;
	using position_t = linked_binary_tree_position<T>;
	using node_t = linked_binary_tree_node<T>;
	explicit linked_binary_tree() = default;

	// TODO : implement copy ctor, copy assignment, destructor
	linked_binary_tree(linked_binary_tree const& rhs) = delete;
	linked_binary_tree& operator=(linked_binary_tree const& rhs) = delete;

	~linked_binary_tree()
	{
		if (root_ == nullptr) return;
		for (auto pos : positions())
		{
			delete pos.v_;
		}
	}

	std::size_t size() const { return size_; }
	bool empty() const { return size_ == 0; }
	position_t root() const { return position_t(root_); }

	void add_root() 
	{
		if (!empty()) throw std::runtime_error("tree is already non empty");
		root_ = new node_t; 
		size_ = 1;
	}
	
	void expand_external(position_t const& p)
	{
		if (!p.external()) throw std::runtime_error("vertice is not external");
		auto v = p.v_;
		v->left_ = new node_t;
		v->left_->parent_ = v;
		v->right_ = new node_t;
		v->right_->parent_ = v;
		size_ += 2;
	}

	position_t remove_above_external(position_t const& p)
	{
		if (!p.external()) throw std::runtime_error("vertice is not external");
		node_t* below = p.v_;
		node_t* above = below->parent_;
		node_t* sibling = below == above->left_ ? above->right_ : above->left_;
		if (above == root_)
		{
			root_ = sibling;
			sibling->parent_ = nullptr;
		}
		else
		{
			node_t* grandparent = above->parent_;
			if (above == grandparent->left_)	grandparent->left_ = sibling;
			else								grandparent->right_ = sibling;
			sibling->parent_ = grandparent;
		}
		delete below;
		delete above;
		size_ -= 2;
		return position_t(sibling);
	}

	children_t positions() const
	{
		children_t list{};
		if (empty()) return list;
		preorder(root_, list);
		return list;
	}

	position_t trinode_restructure(position_t const& x)
	{
		position_t y = x.parent();
		position_t z = y.parent();
		position_t a, b, c;
		position_t t0, t1, t2, t3;
		// There are four situations for trinode restructuring
		if (x == y.left())
		{
			// x is y's left and y is z's left
			if (y == z.left())
			{
				a = x; b = y; c = z;
				t0 = x.left(); t1 = x.right(); t2 = y.right(); t3 = z.right();
			}
			// x is y's left and y is z's right
			else
			{
				a = z; b = x; c = y;
				t0 = z.left(); t1 = x.left(); t2 = x.right(); t3 = y.right();
			}
		}
		else
		{
			// x is y's right and y is z's left
			if (y == z.left())
			{
				a = y; b = x; c = z;
				t0 = y.left(); t1 = x.left(); t2 = x.right(); t3 = z.right();
			}
			// x is y's right and y is z's right
			else
			{
				a = z; b = y; c = z;
				t0 = z.left(); t1 = y.left(); t2 = x.left(); t3 = x.right();
			}
		}

		// replace subtree rooted at z with subtree rooted at b,
		// we need to make z's parent point to his new child b
		if (z == z.parent().left())		z.parent().v_->left_ = b.v_;
		else							z.parent().v_->right_ = b.v_;
		b.v_->parent_ = z.v_->parent_;

		b.v_->left_ = a.v_;				a.v_->parent_ = b.v_;	// make b's left child and a's parent b
		a.v_->left_ = t0.v_;			t0.v_->parent_ = a.v_;	// make a's left child t0 and t0's parent a
		a.v_->right_ = t1.v_;			t1.v_->parent_ = a.v_;	// make a's right child t1 and t1's parent a
		b.v_->right_ = c.v_;			c.v_->parent_ = b.v_;	// make b's right child c and c's parent b
		c.v_->left_ = t2.v_;			t2.v_->parent_ = c.v_;	// make c's left child t2 and t2's parent c
		c.v_->right_ = t3.v_;			t3.v_->parent_ = c.v_;	// make c's right child t3 and t3's parent c
		return b;
	}

protected:
	void preorder(node_t* v, children_t& positions) const
	{
		positions.push_back(position_t(v));
		if (v->left_) preorder(v->left_, positions);
		if (v->right_) preorder(v->right_, positions);
	}

private:
	node_t* root_{ nullptr };
	std::size_t size_{ 0 };
};

}