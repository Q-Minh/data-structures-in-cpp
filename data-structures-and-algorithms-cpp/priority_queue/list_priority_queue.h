#pragma once

#include <list>
#include <algorithm>
#include <cstddef>

namespace data_structures_cpp {

template <typename T, typename TComparator = std::less<T>>
class list_priority_queue
{
public:
	std::size_t size() const { return list_.size();  }
	bool empty() const { return list_.empty(); }
	
	void push(const T& value)
	{
		/*list_.insert(
			std::upper_bound(list_.cbegin(), list_.cend(), value, comp_),
			value
		);*/
		auto it = list_.begin();
		while (it != list_.end() && comp_(*it, value)) ++it;
		list_.insert(it, value);
	}

	const T& front() const { return list_.front(); }
	void pop() { list_.pop_front(); }
protected:
	std::list<T> list_;
	TComparator comp_;
};

template <typename T>
struct list_priority_queue_traits
{
	using list_t = typename std::list<T>;
};

}