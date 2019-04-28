#pragma once

#include <cstddef>
#include <memory>
#include <algorithm>
#include <vector>
#include <utility>

#include "utils/utils.h"
#include "multi_way_entry.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t capacity, class Entry = multi_way_entry<K, V, (capacity + 1) / 2, capacity> >
class multi_way_entry_ordered_map
{
public:
	using entry_t = Entry;
	using value_type = typename entry_t::value_type;
	using node_ptr = typename entry_t::node_ptr;
	using node_t = typename entry_t::node_t;
	using key_type = typename entry_t::key_type;
	using array_t = std::vector<std::shared_ptr<entry_t>>;
	using iterator_t = typename array_t::iterator;

	explicit multi_way_entry_ordered_map() 
	{ 
		vector_.reserve(capacity + 1); // reserve memory upfront
	} 

	void build(node_ptr context)
	{
		node_ptr node = std::make_shared<node_t>();
		auto last = std::make_shared<entry_t>(context);
		last->set_node(node);
		vector_.push_back(last);
	}

	std::size_t size() const { return vector_.size() == 0 ? 0 : vector_.size() - 1; }
	bool empty() const { return size() == 0; }
	iterator_t begin() { return vector_.begin(); }
	iterator_t end() { return vector_.end(); }
	iterator_t last() { return vector_.begin() + size(); }

	iterator_t insert(key_type const& key, value_type const& value, node_ptr context)
	{
		return inserter(key, value, context);
	}

	void erase(key_type const& key)
	{
		auto it = find(key);
		if (it == vector_.end()) throw std::runtime_error("no such entry with this key");
		erase(it);
	}

	void erase(iterator_t& it)
	{
		vector_.erase(it);
	}

	iterator_t greater_than(key_type const& key)
	{
		return std::upper_bound(vector_.begin(), vector_.begin() + size(), key,
			[](auto key, auto elem)
		{
			return key < elem->key();
		});
	}

	iterator_t less_than(key_type const& key)
	{
		std::size_t first = lower_bound(key);
		if (first > size())	return vector_.begin() + size();
		if (first == 0)		return vector_.end();
		return vector_.begin() + first - 1;
	}

	iterator_t find(key_type const& key)
	{
		auto first = lower_bound(key);
		return first >= size() ? vector_.end() :
			vector_[first]->key() != key ? vector_.end() :
			vector_.begin() + first;
	}

protected:
	iterator_t inserter(key_type const& key, value_type const& value, node_ptr context)
	{
		if (size() == capacity) throw std::runtime_error("array already full");

		node_ptr node = std::make_shared<node_t>();
		auto inserted = std::make_shared<entry_t>(context, key, value);
		inserted->set_node(node);

		return vector_.insert(
			std::find_if(vector_.cbegin(), vector_.cbegin() + size(),
				[&key](auto elem)
			{
				return elem->key() >= key;
			}),
			inserted
			);
	}

	std::size_t lower_bound(key_type const& key)
	{
		std::size_t i, first = 0, count, step;
		count = size();

		while (count > 0) {
			i = first;
			step = count / 2;
			i += step;
			if (vector_[i]->key() < key) {
				first = ++i;
				count -= step + 1;
			}
			else
				count = step;
		}

		return first;
	}

	std::vector<std::shared_ptr<entry_t>> vector_;
};

}

#include "tree/multi_way_tree_node.h"