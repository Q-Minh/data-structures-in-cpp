#pragma once

#include <utility>
#include <cstddef>
#include <memory>

#include "utils/utils.h"

namespace data_structures_cpp {

template <class K, class V, std::size_t a, std::size_t b> class multi_way_node;

template <class K, class V, std::size_t min, std::size_t max>
class multi_way_entry : public key_value_pair<K, 
									std::pair<	V, 
												std::shared_ptr< multi_way_node<K, V, min, max> >
									>>
{
public:
	using node_ptr = std::shared_ptr< multi_way_node<K, V, min, max> >;
	using key_value_pair_t = key_value_pair<K, std::pair<V, node_ptr >>;
	using key_type = typename key_value_pair_t::key_type;
	using value_type = decltype(key_value_pair_t().value().first);
	using node_t = multi_way_node<K, V, min, max>;

	explicit multi_way_entry(key_type const& key, value_type const& value, node_ptr context)
		: key_value_pair_t(key, std::make_pair(value, nullptr)), node_context_(context)
	{}

	value_type value() { return key_value_pair_t::value().first; }
	node_ptr node() { return key_value_pair_t::value().second; }
	void set_node(node_ptr node) 
	{ 
		key_value_pair_t::value().second = node; 
		key_value_pair_t::value().second->set_parent(this);
	}
	node_ptr context() const { return node_context_; }
	void set_context(node_ptr context) { node_context_ = context; }

private:
	template <class T, class U, std::size_t, std::size_t>
	friend class multi_way_node;
	node_ptr node_context_;
};

}