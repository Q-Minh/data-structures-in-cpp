#pragma once

#include <cstddef>

namespace data_structures_cpp {

template <typename TDerived>
struct complete_binary_tree_traits;

template <template<class> typename T, typename U>
class complete_binary_tree
{
public:
	using position_t = typename complete_binary_tree_traits<T<U>>::position_t;
	std::size_t size() const { return static_cast<T<U>*>(this)->size(); }
	position_t left(position_t const& p) { return static_cast<T<U>*>(this)->left(p); }
	position_t right(position_t const& p) { return static_cast<T<U>*>(this)->right(p); }
	position_t parent(position_t const& p) { return static_cast<T<U>*>(this)->parent(p); }
	bool has_left(position_t const& p) const { return static_cast<T<U>*>(this)->has_left(p); }
	bool has_right(position_t const& p) const { return static_cast<T<U>*>(this)->has_right(p); }
	bool is_root(position_t const& p) const { return static_cast<T<U>*>(this)->is_root(); }
	position_t root() { return static_cast<T<U>*>(this)->root(); }
	position_t last() { return static_cast<T<U>*>(this)->last(); }
	void add(U const& value) { return static_cast<T<U>*>(this)->add(value); }
	void remove() { static_cast<T<U>*>(this)->remove(); }
	void swap(position_t const& p, position_t const& q) { static_cast<T<U>*>(this)->swap(p, q); }
};

}