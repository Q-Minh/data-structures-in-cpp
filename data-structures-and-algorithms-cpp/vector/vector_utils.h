#pragma once

#include <type_traits>

#include "list/doubly_linked_list.h"

namespace data_structures_cpp {
namespace detail {

template <typename T>
struct underlying_array
{
	using array_type = T * ;
};

template <template<class> typename T, typename U>
struct is_valid_vector_underlying_structure
{
	static constexpr bool value =
		std::is_same<T<U>, doubly_linked_list<U>>::value;
};

template <template<class> typename T, typename U>
using is_valid_vector_underlying_structure_v = typename is_valid_vector_underlying_structure<T, U>::value;

} }
