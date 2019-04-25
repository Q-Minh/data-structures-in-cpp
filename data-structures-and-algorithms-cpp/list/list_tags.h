#pragma once

namespace data_structures_cpp {

template <typename T> class singly_linked_list;
template <typename T> class doubly_linked_list;

struct tags
{
	struct singly_linked_list {};
	struct doubly_linked_list {};
};

namespace detail {

template <typename T>
struct list_type;

template <>
struct list_type<data_structures_cpp::tags::singly_linked_list>
{
	template <typename U>
	using type = typename data_structures_cpp::singly_linked_list<U>;
};

template <>
struct list_type<data_structures_cpp::tags::doubly_linked_list>
{
	template <typename U>
	using type = typename data_structures_cpp::doubly_linked_list<U>;
};

} }

#include "singly_linked_list.h"
#include "doubly_linked_list.h"