#pragma once

#include <cstddef>

#include "utils/utils.h"
#include "linked_binary_tree.h"

namespace data_structures_cpp {

template <class K, class V, class Entry = key_value_pair<K, V>>
class binary_search_tree
{
public:
	using entry_t = Entry;
	using binary_tree_t = linked_binary_tree<entry_t>;
	using position_t = typename binary_tree_t::position_t;
	using key_type = typename Entry::key_type;
	using value_type = typename Entry::value_type;
	class iterator;

	explicit binary_search_tree() : tree_(), size_(0) 
	{
		tree_.add_root();
		tree_.expand_external(tree_.root());
	}

	std::size_t size() const { return size_; }
	bool empty() const { return size_ == 0; }
	
	iterator find(key_type const& k)
	{
		position_t pos = finder(k, root());
		if (!pos.external()) return iterator(pos);
		else return end();
	}

	iterator insert(key_type const& k, value_type const& v)
	{
		return iterator(inserter(k, v));
	}

	void erase(key_type const& k)
	{
		position_t pos = finder(k, root());
		if (pos.external()) throw std::runtime_error("element doesn't exist");
		eraser(pos);
	}

	void erase(iterator& it)
	{
		eraser(it.pos_);
	}
	
	iterator begin()
	{
		position_t leftmost = root();
		while (!leftmost.external()) leftmost = leftmost.left();
		return iterator(leftmost.parent());
	}

	iterator end()
	{
		return iterator(tree_.root());
	}

protected:
	position_t root() const { return tree_.root().left(); }

	position_t finder(key_type const& k, position_t const& pos)
	{
		if (pos.external()) return pos;
		if (k < (*pos).key_) return finder(k, pos.left());
		else if ((*pos).key_ < k) return finder(k, pos.right());
		else return pos;
	}

	position_t inserter(key_type const& k, value_type const& v)
	{
		position_t pos = finder(k, root());
		while (!pos.external()) pos = finder(k, pos.right());
		tree_.expand_external(pos);
		(*pos).key_ = k;
		(*pos).value_ = v;
		++size_;
		return pos;
	}

	position_t eraser(position_t& pos)
	{
		position_t remove_pos;
		if (pos.left().external()) remove_pos = pos.left();
		else if (pos.right().external()) remove_pos = pos.right();
		else
		{
			iterator it(pos); ++it; // find next node in inorder traversal
			(*pos).key_ = (*it.pos_).key_;
			(*pos).value_ = (*it.pos_).value_;
			remove_pos = it.pos_.left(); // get his left external child
		}
		--size_;
		return tree_.remove_above_external(remove_pos);
	}

	position_t trinode_restructure(position_t const& x)
	{
		return tree_.trinode_restructure(x);
	}
private:
	binary_tree_t tree_;
	std::size_t size_;
public:
	class iterator
	{
	private:
		position_t pos_;
	public:
		friend class binary_search_tree<K, V, Entry>;
		iterator(position_t const& pos) : pos_(pos) {}

		entry_t const& operator*() const { return *pos_; }
		entry_t& operator*() { return *pos_; }
		entry_t* operator->() { return &(*pos_); }
		position_t& position() { return pos_; }
		bool operator==(iterator const& rhs) const { return pos_ == rhs.pos_; }
		bool operator!=(iterator const& rhs) const { return !(*this == rhs); }

		iterator& operator++()
		{
			position_t successor = pos_.right();
			if (!successor.external())
			{
				do { pos_ = successor; successor = successor.left(); }
				while (!successor.external());
			}
			else
			{
				successor = pos_.parent();
				while (pos_ == successor.right())
				{
					pos_ = successor;
					successor = successor.parent();
				}
				pos_ = successor;
			}
			return *this;
		}
	};
};

}