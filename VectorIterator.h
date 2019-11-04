//
// Created by Mairenn on 2019-06-02.
//

#ifndef LAB4_VECTORITERATOR_H
#define LAB4_VECTORITERATOR_H


#include <iostream>

template <typename _DataType>
class Vector;

template <typename _DataType>
class VectorIterator
{
private:
    _DataType* m_ptr;
public:
    VectorIterator() { m_ptr = nullptr; }
    VectorIterator(const Vector<_DataType> &p_vector, size_t p_index);
    explicit VectorIterator(_DataType *p_ptr) : m_ptr(p_ptr) {}
    //VectorIterator(const Vector<_DataType> *vector, );
    VectorIterator(const VectorIterator<_DataType>& p_iterator) : m_ptr(p_iterator.m_ptr) {} // copy constructor
    ~VectorIterator() {}

    VectorIterator& operator++();
    VectorIterator& operator--();
    VectorIterator operator++(int);
    VectorIterator operator--(int);

    _DataType& operator*() { return *m_ptr; }

    VectorIterator& operator=(const VectorIterator<_DataType>& p_vector_iterator);

    bool operator<  (const VectorIterator &p_iterator) const { return m_ptr < p_iterator.m_ptr; }
    bool operator<= (const VectorIterator &p_iterator) const { return m_ptr <= p_iterator.m_ptr; }
    bool operator>  (const VectorIterator &p_iterator) const { return m_ptr > p_iterator.m_ptr; }
    bool operator>= (const VectorIterator &p_iterator) const { return m_ptr >= p_iterator.m_ptr; }
    bool operator== (const VectorIterator &p_iterator) const { return m_ptr == p_iterator.m_ptr; }
    bool operator!= (const VectorIterator &p_iterator) const { return m_ptr != p_iterator.m_ptr; }

    VectorIterator operator+(int p_offset) const;
    VectorIterator operator-(int p_offset) const;

    VectorIterator& operator+=(int p_offset);
    VectorIterator& operator-=(int p_offset);

    _DataType* operator->() { return m_ptr; }
    std::ptrdiff_t operator-(const VectorIterator &p_iterator) const { return m_ptr - p_iterator.m_ptr; }

    operator _DataType() { return *m_ptr; }
};

template <typename _DataType>
VectorIterator<_DataType>::VectorIterator(const Vector<_DataType> &p_vector, size_t p_index)
{
    m_ptr = p_vector[p_index];
}

template <typename _DataType>
VectorIterator<_DataType>& VectorIterator<_DataType>::operator++()
{
    ++m_ptr;
    return *this;
}

template <typename _DataType>
VectorIterator<_DataType>& VectorIterator<_DataType>::operator--()
{
    --m_ptr;
    return *this;
}

template <typename _DataType>
VectorIterator<_DataType> VectorIterator<_DataType>::operator++(int)
{
    VectorIterator it(*this);
    ++m_ptr;
    return *this;
}

template <typename _DataType>
VectorIterator<_DataType> VectorIterator<_DataType>::operator--(int)
{
    VectorIterator it(*this);
    --m_ptr;
    return *this;
}

template <typename _DataType>
VectorIterator<_DataType>& VectorIterator<_DataType>::operator=(const VectorIterator<_DataType>& p_iterator)
{
    if (this == &p_iterator)
        return *this;
    m_ptr = p_iterator.m_ptr;
    //m_ptr = p_iterator->m_ptr;
    return (*this);
}

template <typename _DataType>
VectorIterator<_DataType>& VectorIterator<_DataType>::operator+=(int p_offset)
{
    m_ptr += p_offset;
    return *this;
}

template <typename _DataType>
VectorIterator<_DataType>& VectorIterator<_DataType>::operator-=(int p_offset)
{
    m_ptr -= p_offset;
    return *this;
}

template <typename _DataType>
VectorIterator<_DataType> VectorIterator<_DataType>::operator+(int p_offset) const
{
    VectorIterator it(*this);
    return it += p_offset;
}

template <typename _DataType>
VectorIterator<_DataType> VectorIterator<_DataType>::operator-(int p_offset) const
{
    VectorIterator it(*this);
    return it -= p_offset;
}


#endif //LAB4_VECTORITERATOR_H
