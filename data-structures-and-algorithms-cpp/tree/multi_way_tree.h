#pragma once

#include <utility>
#include <cstddef>

#include "utils/utils.h"
#include "map/array_ordered_map.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t a, std::size_t b> class multi_way_node;

template <class K, class V, std::size_t min, std::size_t max>
class multi_way_entry : public key_value_pair<K, std::pair<V, multi_way_node<K, V, min, max>* >>
{
public:
	using key_value_pair_t = key_value_pair<K, std::pair<V, multi_way_node<K, V, min, max>* >>;
	using key_type = typename key_value_pair_t::key_type;
	using value_type = decltype(key_value_pair_t().value().first);
	using node_ptr = multi_way_node<K, V, min, max>*;

	explicit multi_way_entry(key_type const& key = key_type(), value_type const& value = value_type(), bool terminal = true) 
		: key_value_pair_t(key, std::make_pair(value, nullptr)), terminal_(terminal) 
	{}

	value_type value() const { return key_value_pair_t::value().first; }
	node_ptr node() const { return key_value_pair_t::value().second; }
	constexpr bool terminal() { return terminal_; }

private:
	template <class T, class U, std::size_t, std::size_t>
	friend class multi_way_node;
	bool terminal_;
};

template <class K, class V, std::size_t a, std::size_t b>
class multi_way_node : public array_ordered_map<K, V, b, multi_way_entry<K, V, a, b>>
{
public:
	using entry_t = multi_way_entry<K, V, a, b>;
	using map_t = array_ordered_map<K, V, b, entry_t>;
	using key_type = typename entry_t::key_type;
	using value_type = typename entry_t::value_type;
	using node_ptr = typename entry_t::node_ptr;
	using iterator_t = typename map_t::iterator_t;

	void insert(key_type const& key, value_type const& value)
	{
		if (size() == b - 1)
		{

		}
		iterator_t inserted = inserter(key, value);
		if (size() == b - 1) inserted->terminal_ = true;
	}
private:

};

}