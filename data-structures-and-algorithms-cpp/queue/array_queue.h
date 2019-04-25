#pragma once

#include <exception>
#include <utility>

namespace data_structures_cpp {

template <typename T, std::size_t default_capacity = 100>
class array_queue
{
public:
	using value_type = T;

	explicit array_queue(std::size_t capacity = default_capacity)
		: array_(new T[capacity]), capacity_(capacity)
	{ }

	~array_queue()
	{
		delete[] array_;
	}

	std::size_t size() const
	{
		return size_;
	}

	bool empty() const
	{
		return size_ == 0;
	}

	const T& front() const
	{
		if (empty()) throw std::runtime_error("empty queue");
		return array_[front_];
	}

	template <typename U>
	void push_back(U&& value)
	{
		if (size_ == capacity_) throw std::runtime_error("queue full");
		array_[back_] = std::forward<U>(value);
		back_ = (back_ + 1) % capacity_;
		++size_;
	}

	void pop_front()
	{
		if (empty()) throw std::runtime_error("empty queue");
		front_ = (front_ + 1) % capacity_;
		--size_;
	}

private:
	T* array_;
	std::size_t size_{ 0 }, back_{ 0 }, front_{ 0 };
	std::size_t capacity_;
};

}