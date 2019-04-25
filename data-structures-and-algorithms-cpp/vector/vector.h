#pragma once

#include <exception>
#include <utility>
#include <cstddef>

#include "vector_utils.h"

namespace data_structures_cpp {

template <typename T, template<class> typename UnderlyingStructure = detail::underlying_array> class vector;

template <typename T>
class vector<T, detail::underlying_array>
{
	using array_t = typename detail::underlying_array<T>::array_type;

public:
	struct iterator
	{
		using type = T * ;
		using position_t = std::size_t;
		using const_position_t = std::size_t const;
	};
	using iterator_t = typename iterator::type;
	using const_iterator_t = typename const iterator::type;
	using position_t = typename iterator::position_t;
	using const_position_t = typename iterator::const_position_t;

	explicit vector(std::size_t capacity = 2) : size_(0), capacity_(capacity), array_(new T[capacity]) {}

	~vector() { delete[] array_; }

	std::size_t size() const
	{
		return size_;
	}

	std::size_t capacity() const
	{
		return capacity_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	iterator_t begin() const
	{
		if (empty()) return end();
		return array_;
	}

	iterator_t end() const
	{
		return &array_[size_];
	}

	const T& operator[](const_position_t index) const
	{
		return array_[index];
	}

	T& operator[](const_position_t index)
	{
		return array_[index];
	}

	const T& at(const_position_t index) const
	{
		return at(index);
	}

	T& at(const_position_t index)
	{
		if (index >= size_) throw std::runtime_error("index out of bounds");
		return array_[index];
	}

	void erase(const_position_t index)
	{
		if (index >= size_) throw std::runtime_error("index out of bounds");
		for (std::size_t j = index + 1; j < size_; ++j)
		{
			array_[j - 1] = array_[j];
		}
		--size_;
	}

	void reserve(std::size_t const n)
	{
		if (capacity_ >= n) return;
		array_t a = new T[n];
		for (std::size_t i = 0; i < size_; ++i)
		{
			a[i] = array_[i];
		}
		delete[] array_;
		array_ = a;
		capacity_ = n;
	}

	template <typename U>
	void insert(const_position_t index, U&& value)
	{
		if (size_ >= capacity_) reserve(2 * capacity_);
		for (std::size_t i = size_; i > index; --i)
		{
			array_[i] = array_[i - 1];
		}
		array_[index] = std::forward<U>(value);
		++size_;
	}

	template <typename U>
	void push_back(U&& value)
	{
		insert(size_, std::forward<U>(value));
	}

	void pop_back()
	{
		erase(size_ - 1);
	}
private:
	std::size_t size_;
	std::size_t capacity_;
	array_t array_;
};

template <typename T, template<class> typename UnderlyingStructure>
class vector : protected UnderlyingStructure<T>
{
public:
	struct iterator
	{
		using type = iterator;
		using position_t = std::size_t;
		using const_position_t = std::size_t const;
		T& operator*() { return *(ptr_->value_ptr_); }
		bool operator==(iterator const& it) const { return ptr_ == it.ptr_; }
		bool operator!=(iterator const& it) const { return ptr_ != it.ptr_; }
		iterator& operator++() { ptr_ = ptr_->next_; return *this; }
		iterator& operator--() { ptr_ = ptr_->prev_; return *this; }
		iterator operator+(position_t pos) 
		{
			iterator it{ ptr_ };
			for (position_t i = 0; i < pos; ++i) ++it;
			return it;
		}
		position_t operator-(iterator const& it)
		{
			return ptr_ - it.ptr_;
		}
		typename UnderlyingStructure<T>::node_type* operator&() { return ptr_; }
	private:
		friend class vector;
		using ptr_t = typename UnderlyingStructure<T>::node_type *;
		ptr_t ptr_;
		iterator(ptr_t ptr) { ptr_ = ptr; }
	};
	using iterator_t = typename iterator::type;
	using const_iterator_t = typename const iterator::type;
	using position_t = typename iterator::position_t;
	using const_position_t = typename iterator::const_position_t;

	explicit vector() : UnderlyingStructure<T>(), size_(0)
	{
		static_assert(detail::is_valid_vector_underlying_structure<UnderlyingStructure, T>::value,
			"underlying structure must be built-in array or doubly_linked_list");
	}

	std::size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	iterator_t begin() const
	{
		return iterator_t{ this->head()->next_ };
	}

	iterator_t end() const
	{
		return iterator_t{ this->tail() };
	}

	const T& operator[](const_position_t index) const
	{
		return *(begin() + index);
	}

	T& operator[](const_position_t index)
	{
		return *(begin() + index);
	}

	const T& at(const_position_t index) const
	{
		if (index >= size_) throw std::runtime_error("index out of bounds");
		return (*this)[index];
	}

	T& at(const_position_t index)
	{
		if (index >= size_) throw std::runtime_error("index out of bounds");
		return (*this)[index];
	}

	void erase(const_position_t index)
	{
		if (index >= size_) throw std::runtime_error("index out of bounds");
		this->do_remove(&(begin() + index));
		--size_;
	}

	template <typename U>
	void insert(const_position_t index, U&& value)
	{
		this->do_insert(&(begin() + index + 1), std::forward<U>(value));
		++size_;
	}

	template <typename U>
	void push_back(U&& value)
	{
		insert(size_, std::forward<U>(value));
	}

	void pop_back()
	{
		erase(size_ - 1);
	}
private:
	std::size_t size_;
};
}
