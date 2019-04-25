#pragma once

#include <vector>
#include <utility>

#include "complete_binary_tree.h"

namespace data_structures_cpp {

template <typename T>
class vector_complete_binary_tree : complete_binary_tree<vector_complete_binary_tree, T>
{
public:
	using position_t = typename std::vector<T>::iterator;
	explicit vector_complete_binary_tree() : vector_(1) {}
	std::size_t size() const { return vector_.size() - 1; }
	position_t left(position_t const& p) { return pos(2 * index_of(p)); }
	position_t right(position_t const& p) { return pos(2 * index_of(p) + 1); }
	position_t parent(position_t const& p) { return pos(index_of(p) / 2); }
	bool has_left(position_t const& p) const { return 2 * index_of(p) <= size(); }
	bool has_right(position_t const& p) const { return 2 * index_of(p) + 1 <= size(); }
	bool is_root(position_t const& p) const { return index_of(p) == 1; }
	position_t root() { return pos(1); }
	position_t last() { return pos(size()); }
	void add(T const& value) { return vector_.push_back(value); }
	void remove() { vector_.pop_back(); }
	void swap(position_t const& p, position_t const& q) { std::swap(*p, *q); }
protected:
	position_t pos(std::size_t i) { return vector_.begin() + i; }
	std::size_t index_of(position_t const& p) const { return p - vector_.cbegin(); }
private:
	std::vector<T> vector_;
};

template <typename T>
struct complete_binary_tree_traits<vector_complete_binary_tree<T>>
{
	using position_t = typename std::vector<T>::iterator;
};

}