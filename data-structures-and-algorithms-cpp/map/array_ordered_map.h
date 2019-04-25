#pragma once

#include <cstddef>
#include <algorithm>
#include <vector>
#include "utils/utils.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t capacity, class Entry = key_value_pair<K,V>>
class array_ordered_map
{
public:
	using entry_t = Entry;
	using value_type = typename entry_t::value_type;
	using key_type = typename entry_t::key_type;
	using array_t = std::vector<entry_t>;
	using iterator_t = typename array_t::iterator;

	explicit array_ordered_map() { vector_.reserve(capacity); } // reserve memory upfront

	std::size_t size() const { return vector_.size(); }
	bool empty() const { return size() == 0; }
	iterator_t begin() { return vector_.begin(); }
	iterator_t end() { return vector_.end(); }
	
	void insert(key_type const& key, value_type const& value)
	{ 
		if (size() == capacity) throw std::runtime_error("array already full");
		vector_.insert(
			std::find_if(vector_.cbegin(), vector_.cend(),
				[&key](auto elem)
				{
					return elem.key() >= key;
				}
			),
			entry_t(key, value)
		);
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
		return std::upper_bound(vector_.begin(), vector_.end(), key,
			[](auto key, auto elem)
		{
			return key < elem.key();
		});
	}

	iterator_t less_than(key_type const& key)
	{
		std::size_t first = lower_bound(key);
		return first >= vector_.size() ? vector_.end() :
			first == 0 ? vector_.end() :
			vector_.begin() + first - 1;
	}

	iterator_t find(key_type const& key) 
	{ 
		auto first = lower_bound(key);
		return first >= vector_.size() ? vector_.end() : 
			vector_[first].key() != key ? vector_.end() : 
			vector_.begin() + first;
	}

protected:
	std::size_t lower_bound(key_type const& key)
	{
		std::size_t i, first = 0, count, step;
		count = vector_.size();

		while (count > 0) {
			i = first;
			step = count / 2;
			i += step;
			if (vector_[i].key() < key) {
				first = ++i;
				count -= step + 1;
			}
			else
				count = step;
		}

		return first;
	}

private:
	std::vector<entry_t> vector_;
};

}