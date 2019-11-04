//
// Created by Mairenn on 2019-06-02.
//

#ifndef LAB3_VECTOR_H
#define LAB3_VECTOR_H


#include "VectorIterator.h"
#include "VectorException.h"

template <typename _DataType>
class Vector
{
private:
    size_t m_size = 3;
    size_t m_capacity;
    _DataType* m_vector;
public:
    typedef VectorIterator<_DataType> iterator;

    Vector() : m_size(0),
               m_capacity(0),
               m_vector(nullptr) {}

    Vector(size_t p_size, const _DataType &p_dataType = *(new _DataType()));

    template<typename _IteratorType>
    Vector(_IteratorType iteratorBegin, _IteratorType iteratorEnd);

    explicit Vector(const std::initializer_list<_DataType>& p_list);
    Vector(const Vector &p_vector);
    Vector(Vector &&p_vector);

    ~Vector();

    Vector<_DataType>& operator= (const Vector<_DataType> &p_vector);
    Vector<_DataType>& operator= (Vector<_DataType> &&p_vector);
    _DataType& operator[] (size_t p_ind);
    const _DataType& operator[] (size_t p_ind) const;

    _DataType& at(size_t idx);
    iterator begin();
    iterator end();

    template <typename _T>
    void pushBack(_T&& elem)
    {
        if(m_capacity==0)
            reserve(10);
        insert(end(), std::forward<_T>(elem));
    }

    void popBack();

    iterator insert(iterator pos, _DataType& element);

    template<typename _IteratorType>
    iterator insert(iterator pos, _IteratorType iteratorBegin, _IteratorType iteratorEnd);

    iterator erase(iterator pos);
    void reserve(size_t p_capcity);
    void resize(size_t p_size);
    bool empty() const;

    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    void clear();
};

template <typename _DataType>
Vector<_DataType>::Vector(size_t p_size, const _DataType &p_dataType)
{
    m_size = p_size;
    m_capacity = p_size * 2;
    m_vector = new _DataType[m_capacity];
    for (size_t i = 0; i < p_size; ++i)
        m_vector[i] = p_dataType;
}

template <typename _DataType>
template<typename _IteratorType>
Vector<_DataType>::Vector(_IteratorType iteratorBegin, _IteratorType iteratorEnd) : Vector<_DataType>::Vector(iteratorEnd - iteratorBegin)
{
    if (iteratorBegin >= iteratorEnd)
        throw VectorException("iteratorBegin > iteratorEnd");

    iterator ptr = begin();
    for (_IteratorType curIterator = iteratorBegin; curIterator != iteratorEnd; curIterator++, ptr++)
        *ptr = *curIterator;
}

template <typename _DataType>
Vector<_DataType>::Vector(const std::initializer_list<_DataType>& p_list) : Vector<_DataType>::Vector(static_cast<size_t>(p_list.size()))
{
    _DataType *pos = m_vector;
    for (auto it = p_list.begin(); it != p_list.end(); ++it)
        *(pos++) = *it;
}

template <typename _DataType>
Vector<_DataType>::Vector(const Vector &p_vector)
{
    for (size_t i = 0; i < m_size; ++i)
        m_vector[i].~_DataType();
    delete [] m_vector;

    m_capacity = p_vector.m_capacity;
    m_size = p_vector.m_size;
    m_vector = new _DataType[p_vector.m_capacity];

    for (size_t i = 0; i < m_size; ++i)
        m_vector[i] = p_vector.m_vector[i];
}

template <typename _DataType>
Vector<_DataType>::Vector(Vector &&p_vector)
{
    m_size = p_vector.m_size;
    m_capacity = p_vector.m_capacity;
    m_vector = p_vector.m_vector;
    p_vector.m_vector = nullptr;
    p_vector.m_size = 0;
    p_vector.m_capacity = 0;
}

template <typename _DataType>
Vector<_DataType>::~Vector()
{
    delete [] m_vector;
}

template <typename _DataType>
Vector<_DataType>& Vector<_DataType>::operator= (const Vector<_DataType> &p_vector)
{
    if (this == &p_vector)
        return *this;

    for (size_t i = 0; i < m_size; ++i)
        m_vector[i].~_DataType();
    delete [] m_vector;

    m_capacity = p_vector.m_capacity;
    m_size = p_vector.m_size;
    m_vector = new _DataType[p_vector.m_capacity];
    for (size_t i = 0; i < m_size; ++i)
        m_vector[i] = p_vector.m_vector[i];
    return (*this);
}

template <typename _DataType>
Vector<_DataType>& Vector<_DataType>::operator= (Vector<_DataType> &&p_vector)
{
    m_size = p_vector.m_size;
    m_capacity = p_vector.m_capacity;
    m_vector = p_vector.m_vector;
    p_vector.m_vector = nullptr;
    p_vector.m_size = 0;
    p_vector.m_capacity = 0;
}

template <typename _DataType>
_DataType& Vector<_DataType>::operator[] (size_t p_ind)
{
    if (p_ind >= m_size)
        throw VectorException("Index out of range");
    return m_vector[p_ind];
}

template <typename _DataType>
const _DataType& Vector<_DataType>::operator[] (size_t p_ind) const
{
    return m_vector[p_ind];
}

template <typename _DataType>
_DataType& Vector<_DataType>::at(size_t idx)
{
    if (idx >= m_size)
        throw VectorException("Index out of range");
    return m_vector[idx];
}

template <typename _DataType>
typename Vector<_DataType>::iterator Vector<_DataType>::begin()
{
    return Vector<_DataType>::iterator(m_vector);
}


template <typename _DataType>
typename Vector<_DataType>::iterator Vector<_DataType>::end()
{
    return Vector<_DataType>::iterator(m_vector + m_size);
}

template <typename _DataType>
void Vector<_DataType>::popBack()
{
    if (m_size == 0)
        throw VectorException("Vector is empty");

    m_vector[m_size-1].~_DataType();
    --m_size;
}


template <typename _DataType>
template <typename _IteratorType>
typename Vector<_DataType>::iterator Vector<_DataType>::insert(const iterator pos, _IteratorType iteratorBegin, _IteratorType iteratorEnd)
{
    if(m_capacity==0)
        reserve(10);
    if (iteratorBegin > iteratorEnd)
        throw VectorException("iteratorBegin > iteratorEnd");
    if (pos > end() || pos < begin() )
        throw VectorException("Invalid position");
    if (iteratorBegin == iteratorEnd) return pos;

    iterator position = pos;
    for (_IteratorType cur = iteratorBegin; cur != iteratorEnd; ++cur, ++position)
        insert(position, *cur);
    return pos - 1;
}

template <typename _DataType>
typename Vector<_DataType>::iterator  Vector<_DataType>::insert(iterator pos, _DataType& element)
{
    if (m_capacity==0)
        reserve(10);

    if (m_size == m_capacity)
        reserve(m_capacity*2);
    m_size++;

    _DataType* ptr = m_vector + m_size;
    _DataType* position = pos.operator->();
    for(; ptr > position; --ptr)
        *ptr = *(ptr - 1);
    *(ptr) = element;

    return pos;
}

template <typename _DataType>
typename Vector<_DataType>::iterator Vector<_DataType>::erase(iterator pos)
{
    if (pos > end() || pos < begin() )
        throw VectorException("Invalid position");

    for (VectorIterator<_DataType> ptr = pos; ptr < end() - 1; ++ptr)
        *ptr = *(ptr + 1);

    --m_size;
    return pos;
}

template <typename _DataType>
void Vector<_DataType>::reserve(size_t p_capacity)
{
    if (p_capacity > m_capacity)
    {
        m_capacity = p_capacity;
        _DataType *mas = new _DataType[p_capacity];
        for (int i = 0; i < m_size; ++i)
            mas[i] = m_vector[i];
        delete [] m_vector;

        m_vector = new _DataType[p_capacity];
        for (int i = 0; i < m_size; ++i)
            m_vector[i] = mas[i];
        delete [] mas;
    }
}


template <typename _DataType>
bool Vector<_DataType>::empty() const
{
    return (m_size == 0);
}

template <typename _DataType>
void Vector<_DataType>::resize(size_t p_size)
{
    if (m_capacity == 0) {
        this->reserve(p_size * 2);
    }
    if (p_size < m_size) m_size = p_size;
    if (p_size > m_size && p_size < m_capacity) m_size = p_size;
    if (p_size > m_capacity) {
        this->reserve(m_capacity * 2);
    }
}


template <typename _DataType>
void Vector<_DataType>::clear()
{
    for (size_t i = 0; i < m_size; ++i)
        m_vector[i].~_DataType();
    delete [] m_vector;
    m_size = 0;
    m_capacity = 0;
}

#endif //LAB3_VECTOR_H