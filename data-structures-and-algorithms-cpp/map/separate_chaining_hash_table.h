#pragma once

#include <vector>
#include <list>
#include <cstddef>
#include <exception>

#include "utils/utils.h"

namespace data_structures_cpp {

template <class K, class V, class Hasher> class separate_chaining_hash_table;

template <class K, class V, class Hasher>
class separate_chaining_hash_table
{
public:
	using entry_t = key_value_pair<K const, V>;
	using bucket_t = std::list<entry_t>;
	using bucket_array_t = std::vector<bucket_t>;
	using bucket_iterator_t = typename bucket_array_t::iterator;
	using entry_iterator_t = typename bucket_t::iterator;
	class iterator;

	explicit separate_chaining_hash_table(std::size_t capacity = 101)
		: size_(0), b_array_(capacity)
	{}

	std::size_t size() const { return size_; }
	bool empty() const { return size() == 0; }

	iterator find(K const& k, V const& v)
	{
		iterator it = finder(k);
		if (end_of_bucket(it)) return end();
		else return it;
	}

	iterator put(K const& k, V const& v)
	{
		iterator it = finder(k);
		if (end_of_bucket(it)) return inserter(it, entry_t(k, v));
		else
		{
			it.entry_it_->value_ = v;
			return it;
		}
	}

	void erase(K const& k)
	{
		iterator it = finder(k);
		if (end_of_bucket(it)) throw std::runtime_error("no entry with this key");
		eraser(it);
	}

	void erase(iterator const& it) { eraser(it); }

	iterator begin()
	{
		if (empty()) return end();
		bucket_iterator_t bucket_it = b_array_.begin();
		while (bucket_it->empty()) ++bucket_it;
		return iterator(b_array_, bucket_it, bucket_it->begin());
	}
	iterator end() { return iterator(b_array_, b_array_.end()); }
protected:
	iterator finder(K const& k)
	{
		int i = hash(k) % b_array_.size();
		bucket_iterator_t bucket_it = b_array_.begin() + i;
		iterator it(b_array_, bucket_it, bucket_it->begin());
		while (!end_of_bucket(it) && (*it).key_ != k) next_entry(it);
		return it;
	}

	iterator inserter(iterator const& it, entry_t const& e)
	{
		entry_iterator_t entry_it = it.bucket_it_->insert(it.entry_it_, e);
		++size_;
		return iterator(b_array_, it.bucket_it_, entry_it);
	}

	void eraser(iterator const& it)
	{
		it.bucket_it_->erase(it.entry_it_);
		--size_;
	}

	static void next_entry(iterator& it) { ++it.entry_it_; }
	static bool end_of_bucket(iterator const& it) 
	{ 
		return it.bucket_it_ == it.bucket_array_->end() || it.entry_it_ == it.bucket_it_->end(); 
	}
		
private:
	std::size_t size_;
	Hasher hash;
	bucket_array_t b_array_;

public:
	class iterator
	{
	private:
		entry_iterator_t entry_it_;
		bucket_iterator_t bucket_it_;
		bucket_array_t const * bucket_array_;
	public:
		iterator(bucket_array_t const& a, bucket_iterator_t const& b, entry_iterator_t const& e = entry_iterator_t())
			: entry_it_(e), bucket_it_(b), bucket_array_(&a)
		{}

		entry_t& operator*() const { return *entry_it_; }
		entry_iterator_t operator->() { return entry_it_; }
		bool operator==(iterator const& rhs) const
		{
			if (bucket_array_ != rhs.bucket_array_ || bucket_it_ != rhs.bucket_it_) return false;
			else if (bucket_it_ == bucket_array_->end()) return true;
			else return entry_it_ == rhs.entry_it_;
		}
		bool operator!=(iterator const& rhs) const { return !(*this == rhs); }

		iterator& operator++() 
		{
			++entry_it_;
			if (end_of_bucket(*this))
			{
				++bucket_it_;
				while (bucket_it_ != bucket_array_->end() && bucket_it_->empty()) ++bucket_it_;
				if (bucket_it_ == bucket_array_->end()) return *this;
				entry_it_ = bucket_it_->begin();
			}
			return *this;
		}

		friend class separate_chaining_hash_table<K,V,Hasher>;
	};
};

}