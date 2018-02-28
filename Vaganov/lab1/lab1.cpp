// lab1oop.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>

using namespace std ; 

template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
	}

	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);

		return m_array[index];
	}

	//переписанный конструктор копирования, стандартная функция copy правильно отрабатывает исключения
	Array(const Array& other)
		: m_size(other.m_size),
		m_array(m_size ? new T[m_size] : nullptr)
	{
		copy(other.m_array.get(), other.m_array.get() + m_size, m_array.get());
	}
	//переписанный оператор копирования
	Array & operator = (Array const& object) {
		if (this != &object)
			Array(object).swap(*this);
		return *this;
	}
	// стандартная функция swap (исп. в методе) правильно отрабатывает исключения
	void swap(Array & object1) {
		swap(this->m_size, object.m_size);
		swap(this->m_array, object.m_array);
	}

private:
	size_t m_size;
	unique_ptr<T[]> m_array;			//используем умный указатель вместо обычного
};

int main()
{
    return 0;
}

