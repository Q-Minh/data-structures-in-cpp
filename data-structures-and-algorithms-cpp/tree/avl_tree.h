#pragma once

#include <cstddef>
#include <algorithm>
#include <exception>

#include "utils/utils.h"
#include "binary_search_tree.h"

namespace data_structures_cpp {

template <class K, class V> class avl_tree;

template <class K, class V>
class avl_entry : public key_value_pair<K,V>
{
public:
	friend class avl_tree<K,V>;
	using key_type = typename key_value_pair<K,V>::key_type;
	using value_type = typename key_value_pair<K,V>::value_type;
	
	avl_entry(key_type const& key = key_type(), value_type const& value = value_type())
		: key_value_pair<K,V>(key, value), height_(0)
	{}

	std::size_t height() const { return height_; }
private:
	std::size_t height_;
protected:
	void set_height(std::size_t height) { height_ = height; }
};

template <class K, class V>
class avl_tree : public binary_search_tree<K, V, avl_entry<K, V>>
{
public:
	using entry_t = avl_entry<K, V>;
	using iterator_t = typename binary_search_tree<K, V, avl_entry<K, V>>::iterator;
protected:
	using key_type = typename entry_t::key_type;
	using value_type = typename entry_t::value_type;
	using tree_t = binary_search_tree<K, V, avl_entry<K, V>>;
	using position_t = typename tree_t::position_t;
public:
	explicit avl_tree() : tree_t() {}

	iterator_t insert(key_type const& k, value_type const& v)
	{
		position_t inserted = inserter(k, v);
		set_height(inserted);
		rebalance(inserted);
		return iterator_t(inserted);
	}

	void erase(key_type const& k)
	{
		position_t erased = finder(k, tree_t::root());
		if (iterator(erased) == tree_t::end()) throw std::runtime_error("no such entry with specified key");
		position_t replaced = eraser(pos);
		rebalance(replaced);
	}

	void erase(iterator_t& it)
	{
		position_t replaced = eraser(it.position());
		rebalance(replaced);
	}
protected:
	std::size_t height(position_t const& pos) const { return pos.external() ? 0 : pos->height(); }
	
	void set_height(position_t pos) 
	{ 
		std::size_t left_height = height(pos.left());
		std::size_t right_height = height(pos.right());
		pos->set_height(1 + std::max(left_height, right_height));
	}

	bool balanced(position_t const& pos) const
	{
		int balance = height(pos.left()) - height(pos.right());
		return std::abs(balance) <= 1;
	}

	position_t tall_grandchild(position_t const& pos) const
	{
		position_t left_child = pos.left();
		position_t right_child = pos.right();
		if (height(left_child) >= height(right_child))
		{
			if (height(left_child.left()) >= height(left_child.right())) return left_child.left();
			else return left_child.right();
		}
		else
		{
			if (height(right_child.right()) >= height(right_child.left())) return right_child.right();
			else return right_child.left();
		}
	}

	void rebalance(position_t const& pos)
	{
		position_t z = pos;
		while (!(z == tree_t::root()))
		{
			z = z.parent();
			set_height(z);
			if (!balanced(z))
			{
				position_t x = tall_grandchild(z);
				z = tree_t::trinode_restructure(x);
				set_height(z.left());
				set_height(z.right());
				set_height(z);
			}
		}
	}
};

}