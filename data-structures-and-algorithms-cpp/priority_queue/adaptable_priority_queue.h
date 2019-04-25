#pragma once

#include <cstddef>

#include "list_priority_queue.h"

namespace data_structures_cpp {

template <typename T, typename TComparator> class adaptable_priority_queue;

template <typename T>
class position
{
public:
	T const& operator*() { return *p; }
	// too many friends but oh well
	template <class U, class V> friend class adaptable_priority_queue;
private:
	typename list_priority_queue_traits<T>::list_t::iterator p_;
};

template <typename T, typename TComparator = std::less<T>>
class adaptable_priority_queue : protected list_priority_queue<T, TComparator>
{
public:
	std::size_t size() const { return list_priority_queue<T, TComparator>::size(); }
	bool empty() const { return list_priority_queue<T, TComparator>::empty(); }
	const T& front() const { return list_priority_queue<T, TComparator>::front(); }

	position<T> insert(T const& value) 
	{ 
		position<T> pos{};
		/*pos.p_ = list_.insert(
			std::upper_bound(list_.cbegin(), list_.cend(), value, comp_),
			value
		);*/
		auto it = list_.begin();
		while (it != list_.end() && comp_(*it, value)) ++it;
		pos.p_ = list_.insert(it, value);
		return pos;
	}

	void pop() { return list_priority_queue<T, TComparator>::pop(); }

	void remove(position<T> const& p) { this->list_.erase(p.p_); }

	position<T> replace(position<T> const& p, T const& value) 
	{
		this->list_.erase(p.p_);
		return insert(value);
	}
};

}