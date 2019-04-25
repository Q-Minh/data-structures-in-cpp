#pragma once

#include <memory>

namespace data_structures_cpp {

// Forward declarations
template <typename T> class singly_linked_list;
template <typename T> class doubly_linked_list;
template <typename T> class circular_linked_list;
template <typename T, template<class> typename UnderlyingStructure> class vector;

template <typename T>
class singly_linked_node
{
	friend class singly_linked_list<T>;
	friend circular_linked_list<T>;
private:
	singly_linked_node<T>* next_;
	std::unique_ptr<T> value_ptr_;
};


template <typename T>
class doubly_linked_node
{
	friend class doubly_linked_list<T>;
	friend class vector<T, doubly_linked_list>;
private:
	doubly_linked_node<T>* next_;
	doubly_linked_node<T>* prev_;
	std::unique_ptr<T> value_ptr_;
};

}