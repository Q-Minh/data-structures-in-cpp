#pragma once

#include <algorithm>

#include "separate_chaining_hash_table.h"

namespace data_structures_cpp {

template <class K, class V, class Hasher>
class dictionary : public separate_chaining_hash_table<K, V, Hasher>
{
public:
	using iterator = typename separate_chaining_hash_table<K, V, Hasher>::iterator;
	class range;

	explicit dictionary(int capacity = 101) : separate_chaining_hash_table<K, V, Hasher>(capacity) {}
	
	range find_all(const K& k)
	{
		iterator begin = finder(k);
		iterator end = begin;
		while (!end_of_bucket(end) && (*begin).key_ == (*end).key_)
		{
			++end;
		}
		return range(begin, end);
	}
	
	iterator insert(const K& k, const V& v)
	{
		iterator it = finder(k);
		return inserter(it, entry_t(k, v));
	}

	class range
	{
	public:
		range(iterator const& begin, iterator const& end)
			: begin_(begin), end_(end)
		{}

		iterator const& begin() const { return begin_; }
		iterator const& end() const { return end_; }
		
	private:
		iterator begin_, end_;
	};
};

}