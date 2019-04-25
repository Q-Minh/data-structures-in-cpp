#pragma once

namespace data_structures_cpp {

template <class K, class V, class Entry> class binary_search_tree;
template <class T, class U, class Hasher> class separate_chaining_hash_table;
template <class T, class U, class Hasher> class dictionary;
template <class K, class V> struct key_value_pair;

template <class K, class V>
struct key_value_pair
{
	using value_type = V;
	using key_type = K;

	explicit key_value_pair() = default;
	key_value_pair(key_type const& k, value_type const& v) : key_(k), value_(v) {}
	key_value_pair(key_value_pair const& rhs) = default;
	key_value_pair(key_value_pair&& rhs) = default;
	key_value_pair& operator=(key_value_pair const& rhs) = default;
	bool operator==(key_value_pair const& rhs) const { return key_ == rhs.key_ && value_ == rhs.value_; }
	bool operator<(key_value_pair const& rhs) const { return key_ < rhs.key_; }
	key_type key() const { return key_; }
	value_type value() const { return value_; }
private:
	template <class T, class U, class E>
	friend class binary_search_tree;
	template <class T, class U, class Hasher>
	friend class separate_chaining_hash_table;
	template <class T, class U, class Hasher>
	friend class dictionary;
	key_type key_;
	value_type value_;
};

}