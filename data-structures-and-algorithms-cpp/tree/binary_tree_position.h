#pragma once

namespace data_structures_cpp {

/*
 * binary tree position interface for static polymorphism
 */
template <template<class> typename T, typename U>
class binary_tree_position
{
public:
	U& operator*() { return *static_cast<T<U>>(*this); }
	T<U> left() const { return static_cast<T<U>*>(this)->left(); }
	T<U> right() const { return static_cast<T<U>*>(this)->right(); }
	T<U> parent() const { return static_cast<T<U>*>(this)->parent(); }

	bool root() const { return static_cast<T<U>*>(this)->root(); }
	bool external() const { return static_cast<T<U>*>(this)->external(); }
};

}