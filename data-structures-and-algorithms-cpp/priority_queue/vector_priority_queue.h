#pragma once

#include <cstddef>

#include "tree/vector_complete_binary_tree.h"

namespace data_structures_cpp {

template <typename T, typename TComparator = std::less<T>>
class vector_priority_queue
{
public:
	using tree_t = vector_complete_binary_tree<T>;
	using position_t = typename tree_t::position_t;

	std::size_t size() const { return tree_.size(); }
	bool empty() const { return tree_.size() == 0; }

	void push(const T& value)
	{
		tree_.add(value);
		position_t p = tree_.last();
		while (!tree_.is_root(p))
		{
			position_t q = tree_.parent(p);
			if (!comp_(*p, *q)) break;
			tree_.swap(p, q);
			p = q;
		}
	}

	const T& front() { return *tree_.root(); }
	
	void pop() 
	{ 
		if (size() == 1)
		{
			tree_.remove();
		}
		else
		{
			position_t q = tree_.root();
			tree_.swap(q, tree_.last());
			tree_.remove();
			while (tree_.has_left(q))
			{
				position_t p = tree_.left(q);
				if (tree_.has_right(q) && comp_(*tree_.right(q), *p)) p = tree_.right(q);
				if (comp_(*p, *q))
				{
					tree_.swap(p, q);
					q = p;
				}
				else break;
			}
		}
	}
private:
	vector_complete_binary_tree<T> tree_;
	TComparator comp_;
};

}