#pragma once

#include <utility>
#include <numeric>
#include <cstddef>
#include <memory>
#include <type_traits>

#include "map/array_ordered_map.h"
#include "multi_way_entry.h"

namespace data_structures_cpp {

struct dummy_t {};

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

	explicit multi_way_node() : parent_(nullptr), terminal_(key_type(), value_type(), nullptr) 
	{
		static_assert(std::is_same_v<node_ptr, std::shared_ptr<multi_way_node>>, "entry type must have shared_ptr to node type");
		static_assert(std::is_same_v<key_type, K>, "node type must know entry's key type");
		static_assert(std::is_same_v<value_type, V>, "node type must have same value_type as entry's value type");
	}

	void construct(node_ptr context) { terminal_.set_context(context); }
	iterator_t insert(key_type const& key, value_type const& value, node_ptr context) { return inserter(key, value, context); }
	bool full() const { return size() >= b; }
	entry_t* parent() const { return parent_; }
	void set_parent(entry_t* parent) 
	{ 
		if (parent != nullptr) parent_ = parent; 
	}
	bool external() const { return empty(); }
	entry_t* terminal() { return &terminal_; }
	void clear() { vector_.clear(); terminal_.~entry_t(); }

private:
	entry_t* parent_{ nullptr };
	entry_t terminal_;
};

}
