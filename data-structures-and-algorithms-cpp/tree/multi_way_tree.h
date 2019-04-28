#pragma once

#include <cstddef>
#include <iterator>
#include <memory>
#include <type_traits>
#include <exception>

#include "multi_way_tree_node.h"
#include "multi_way_entry_ordered_map.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t a = 2, std::size_t b = 4>
class multi_way_tree
{
public:
	using node_t = multi_way_node<K, V, a, b>;
	using entry_t = typename node_t::entry_t;
	using map_t = typename node_t::map_t;
	using key_type = typename node_t::key_type;
	using value_type = typename node_t::value_type;
	using iterator_t = typename node_t::iterator_t;
	using node_ptr = typename entry_t::node_ptr;

	// tree_iterator needs to point to individual entries
	// but walk from node to node
	class tree_iterator;

	// accept memory leak for now with root node
	explicit multi_way_tree() : root_(std::make_shared<node_t>()), size_(0)
	{
		static_assert(std::is_same_v<entry_t, multi_way_entry<K, V, a, b>>);
		static_assert(std::is_same_v<iterator_t, typename map_t::iterator_t>, 
			"iterator types must be the same as iterators to the underlying key sequences");
		static_assert(std::is_same_v<map_t, multi_way_entry_ordered_map<key_type, value_type, b, entry_t>>,
			"underlying key sequence type should be an array_ordered_map of size b with key and value types "
			"used by users and multi_way_entry type");
		static_assert(std::is_same_v<decltype(std::iterator_traits<iterator_t>::iterator_category()), iterator_t::iterator_category>,
			"iterator type must have random access property");
		static_assert(std::is_same_v<iterator_t::value_type, std::shared_ptr<entry_t>>,
			"iterator's must be pointers to shared_ptrs to entries");
	}
	multi_way_tree(multi_way_tree const& rhs) = delete;
	multi_way_tree(multi_way_tree&& rhs) = delete;
	multi_way_tree& operator=(multi_way_tree const& rhs) = delete;
	node_ptr root() { return root_; }

	std::size_t size() const { return size_; }
	bool empty() const { return size() == 0; }
	iterator_t begin() const { return root_->begin(); }
	iterator_t end() const { return root_->end(); }

	tree_iterator find(key_type const& key)
	{
		node_ptr entry_node = finder(key, root_);
		return tree_iterator(entry_node->find(key));
	}

	void insert(key_type const& key, value_type const& value)
	{
		node_ptr z, v; iterator_t entry;
		if (empty())
		{
			v = root_;
			v->build();
		}
		else
		{
			z = finder(key, root_);
			while (!z->external())
			{
				iterator_t it = z->find(key);
				z = finder(key, (*it)->node());
			}
			v = z->parent()->context();
		}

		entry = v->insert(key, value);

		// split operation
		while (v->full())
		{
			v = split(v);
		}

		++size_;
	}

protected:
	node_ptr split(node_ptr v)
	{
		node_ptr vp, vpp, parent_node;
		
		if (v == root_)
		{
			parent_node = std::make_shared<node_t>();
			parent_node->build();
		}
		else
		{
			parent_node = v->parent()->context();
		}
		
		iterator_t	removed = v->begin() + b / 2, 
					first = v->begin(), 
					second = v->begin() + b / 2 + 1;

		iterator_t new_entry = parent_node->insert((*removed)->key(), (*removed)->value());
		
		vp = std::make_shared<node_t>(); 
		vp->build();
		vpp = std::make_shared<node_t>();
		vpp->build();
		
		iterator_t moved_entry;
		for (; first != removed; ++first)
		{
			moved_entry = vp->insert((*first)->key(), (*first)->value());
			(*moved_entry)->set_node((*first)->node());
		}
		iterator_t last = vp->last();
		(*last)->set_node((*removed)->node());

		for (; second != v->last(); ++second)
		{
			moved_entry = vpp->insert((*second)->key(), (*second)->value());
			(*moved_entry)->set_node((*second)->node());
		}
		last = vpp->last();
		(*last)->set_node( (* (v->last()) )->node());

		if (v == root_) root_ = parent_node;
		auto entry = *new_entry;
		entry->set_node(vp);
		++new_entry;

		entry = *new_entry;
		entry->set_node(vpp);

		return parent_node;
	}

	node_ptr finder(key_type const& key, node_ptr v)
	{
		if (v->external()) return v;
		iterator_t it = v->find(key);
		// if the key is in this node, return it
		if (it != v->end()) return v;

		it = v->less_than(key);
		// if we find key less than key, we search in the child node of that entry
		if (it != v->end())
		{
			it++;
			return finder(key, (*it)->node());
		}
		// if the key is less than all keys in this node, search in
		// the child node of the first entry of this node
		node_ptr next = (*v->begin())->node();
		return finder(key, next);
	}

private:
	node_ptr root_;
	std::size_t size_{ 0 };

public:
	class tree_iterator
	{
	public:
		explicit tree_iterator(iterator_t entry_it) : entry_it_(entry_it) {}
		std::shared_ptr<entry_t> operator*() { return *entry_it_; }
	
		//tree_iterator& operator++()
		//{
		//	node_ptr context = entry_it_->context();
		//	key_type current_key = entry_it_->key();
		//	// move the node to the next entry in this key sequence
		//	if (entry_it_ != context->end()) ++entry_it_;
		//	// if we've reached the end of this node's key sequence
		//	if (entry_it_ == context->end())
		//	{
		//		// if the terminal entry points to a non-external node,
		//		// the next entry to read is simply the terminal's node's
		//		// first entry
		//		entry_t* next_entry = context->terminal();
		//		if (next_entry->node()->external())
		//		{
		//			// go up until the next entry is not a terminal entry
		//			// or we have reached the root's terminal entry
		//			do
		//			{
		//				next_entry = context->parent();
		//				context = context->parent()->context();
		//			} while (context->parent() != nullptr && next_entry == context->terminal());

		//			entry_it_ = context->greater_than(current_key);
		//		}
		//		else
		//		{
		//			// go down and left until we reach an external node
		//			do
		//			{
		//				entry_it_ = next_entry->node()->begin();
		//				next_entry_ = &(*entry_it_);
		//			} while (!next_entry->node()->external())
		//		}
		//	}
		//	// if we haven't reached the end of this node's key sequence,
		//	// check if we can go down
		//	else
		//	{
		//		// go down left until external
		//		do
		//		{
		//			entry_it_ = entry_it_->node()->begin();
		//			context = entry_it_->context();
		//		} while (!entry_it_->node()->external())
		//	}
		//	return *this;
		//}

	private:
		iterator_t entry_it_;
	};
};

}