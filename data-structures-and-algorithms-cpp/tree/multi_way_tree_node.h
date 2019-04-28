#pragma once

#include <utility>
#include <numeric>
#include <cstddef>
#include <memory>
#include <type_traits>

#include "multi_way_entry.h"
#include "multi_way_entry_ordered_map.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t a, std::size_t b>
class multi_way_tree_node : public std::enable_shared_from_this<multi_way_tree_node<K, V, a, b>>
{
public:
	using entry_t = multi_way_entry<K, V, a, b>;
	using map_t = multi_way_entry_ordered_map<K, V, b, entry_t>;
	using key_type = typename entry_t::key_type;
	using value_type = typename entry_t::value_type;
	using node_ptr = typename entry_t::node_ptr;
	using iterator_t = typename map_t::iterator_t;

	explicit multi_way_tree_node(std::shared_ptr<entry_t> parent = nullptr) : parent_(parent), map_()
	{
		static_assert(std::is_same_v<node_ptr, std::shared_ptr<multi_way_tree_node>>, "entry type must have shared_ptr to node type");
		static_assert(std::is_same_v<key_type, K>, "node type must know entry's key type");
		static_assert(std::is_same_v<value_type, V>, "node type must have same value_type as entry's value type");
	}

	void build() { map_.build(shared_from_this()); }

	std::size_t size() const { return map_.size(); }
	bool empty() const { return size() == 0; }
	iterator_t begin() { return map_.begin(); }
	iterator_t end() { return map_.end(); }
	iterator_t last() { return map_.last(); }

	void erase(key_type const& key) { map_.erase(key); }
	void erase(iterator_t& it) { map_.erase(it); }
	iterator_t greater_than(key_type const& key) { return map_.greater_than(key); }
	iterator_t less_than(key_type const& key) { return map_.less_than(key); }
	iterator_t find(key_type const& key) { return map_.find(key); }
	iterator_t insert(key_type const& key, value_type const& value) { return map_.insert(key, value, shared_from_this()); }

	bool full() const { return size() >= b; }
	std::shared_ptr<entry_t> parent() const { return parent_; }
	void set_parent(std::shared_ptr<entry_t> parent) { parent_ = parent; }
	bool external() const { return empty(); }

private:
	std::shared_ptr<entry_t> parent_;
	map_t map_;
};

}
