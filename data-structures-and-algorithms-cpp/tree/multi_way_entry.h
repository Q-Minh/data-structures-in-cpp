#pragma once

#include <utility>
#include <cstddef>
#include <memory>

#include "utils/utils.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t a, std::size_t b> class multi_way_tree_node;

template <class K, class V, std::size_t min, std::size_t max>
class multi_way_entry : public key_value_pair<K, 
									std::pair<	V, 
												std::shared_ptr< multi_way_tree_node<K, V, min, max> >
									>>,
						public std::enable_shared_from_this<multi_way_entry<K, V, min, max>>
{
public:
	using node_ptr = std::shared_ptr< multi_way_tree_node<K, V, min, max> >;
	using key_value_pair_t = key_value_pair<K, std::pair<V, node_ptr >>;
	using key_type = typename key_value_pair_t::key_type;
	using value_type = decltype(key_value_pair_t().value().first);
	using node_t = multi_way_tree_node<K, V, min, max>;

	explicit multi_way_entry(node_ptr context, key_type const& key = key_type(), value_type const& value = value_type())
		: key_value_pair_t(key, std::make_pair(value, nullptr)), context_(context)
	{}

	value_type value() { return key_value_pair_t::value().first; }
	void set_value(value_type const& value) { key_value_pair_t::value().first = value; }
	node_ptr node() { return key_value_pair_t::value().second; }
	void set_node(node_ptr node) 
	{ 
		key_value_pair_t::value().second = node;
		key_value_pair_t::value().second->set_parent(shared_from_this());
	}
	node_ptr context() { return context_; }

private:
	template <class T, class U, std::size_t, std::size_t>
	friend class multi_way_tree_node;
	node_ptr context_;
};

}