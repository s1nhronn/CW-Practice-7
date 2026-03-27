#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cassert>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

// Домашнее задание
// 1. Реализовать итераторы для вектора
// 2. Придумать еще 3 insert (один уже есть) и 3 erase, но с итераторами

namespace topit
{
  template < class T >
  struct Vector
  {
    Vector();
    Vector(const Vector< T >&);
    Vector(Vector< T >&&) noexcept;

    ~Vector();
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&) noexcept;

    void swap(Vector< T >& rhs) noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void pushBack(const T&);
    void popBack();
    void pushFront(const T&);
    void popFront();

    // Классная работа
    // Строгая гарантия, copy-and-swap, тесты
    void insert(size_t i, const T& val);
    void erase(size_t i);
    void insert(size_t i, const Vector< T >& rhs, size_t beg, size_t end);
    void erase(size_t beg, size_t end);

    // Вместо VecIterator свой итератор
    template < class VecIterator, class FwdIterator >
    void insert(VecIterator pos, FwdIterator beg, FwdIterator end); // один из методов

  private:
    T* data_;
    size_t size_, capacity_;

    explicit Vector(size_t k);
  };
}

template < class T >
void topit::Vector< T >::erase(size_t beg, size_t end) // !FIXME
{
  if (!size_)
  {
    throw std::out_of_range("Erasing from empty vector");
  }
  if (end > size_)
  {
    throw std::range_error("End more than size");
  }
  if (beg > end)
  {
    throw std::range_error("Begin more than end");
  }
  size_t rem = end - beg;
  Vector< T > cpy(size_ - rem);
  for (size_t i = 0; i < beg; ++i)
  {
    cpy[i] = (*this)[i];
  }
  for (size_t i = beg; i < cpy.getSize(); ++i)
  {
    cpy[i] = (*this)[i + rem];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::insert(size_t i, const Vector< T >& rhs, size_t beg, size_t end)
{
  if (i > size_)
  {
    throw std::out_of_range("Index more than size");
  }
  if (end > rhs.getSize())
  {
    throw std::range_error("End index more than size of rhs");
  }
  if (end < beg)
  {
    throw std::range_error("End less than begin");
  }
  size_t add = end - beg;
  Vector< int > cpy(size_ + add);
  for (size_t j = 0; j < i; ++j)
  {
    cpy[j] = (*this)[j];
  }
  for (size_t j = i; j < i + add; ++j)
  {
    cpy[j] = rhs[beg + j - i];
  }
  for (size_t j = i + add; j < cpy.getSize(); ++j)
  {
    cpy[j] = (*this)[j - add];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("Index is more than size");
  }
  Vector< T > cpy(size_ - 1);
  for (size_t j = 0; j < i; ++j)
  {
    cpy[j] = (*this)[j];
  }
  for (size_t j = i + 1; j < size_; ++j)
  {
    cpy[j - 1] = (*this)[j];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::insert(size_t i, const T& val)
{
  if (i > size_)
  {
    throw std::out_of_range("Index is more than size");
  }
  Vector< T > cpy(size_ + 1);
  for (size_t j = 0; j < i; ++j)
  {
    cpy[j] = (*this)[j];
  }
  cpy[i] = val;
  for (size_t j = i + 1; j < cpy.getSize(); ++j)
  {
    cpy[j] = (*this)[j - 1];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::popBack()
{
  if (size_ == 0)
  {
    throw std::out_of_range("Vector is empty");
  }
  data_[size_ - 1].~T();
  --size_;
}

template < class T >
void topit::Vector< T >::popFront()
{
  if (size_ == 0)
  {
    throw std::out_of_range("Vector is empty");
  }
  Vector< T > cpy(size_ - 1);
  for (size_t i = 1; i < size_; ++i)
  {
    cpy[i - 1] = (*this)[i];
  }
  swap(cpy);
}

template < class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template < class T >
void topit::Vector< T >::pushFront(const T& val)
{
  Vector< T > cpy(size_ + 1);
  cpy[0] = val;
  for (size_t i = 1; i < cpy.getSize(); ++i)
  {
    cpy[i] = (*this)[i - 1];
  }
  swap(cpy);
}

template < class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(rhs.data_, data_);
  std::swap(rhs.size_, size_);
  std::swap(rhs.capacity_, capacity_);
}

template < class T >
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T >* cthis = this;
  const T& ret = (*cthis)[id];
  return const_cast< T& >(ret);
}

template < class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  assert(id < getSize());
  return data_[id];
}

template < class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  const T& ret = cthis->at(id);
  return const_cast< T& >(ret);
  // return const_cast< T& >(static_cast< const Vector< T >* >(this)->at(id))
}

template < class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (getSize() && id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

template < class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template < class T >
topit::Vector< T >::Vector(size_t k):
  data_(new T[k]),
  size_(k),
  capacity_(k)
{}

template < class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(rhs);
  swap(cpy);
  return *this;
}

template < class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template < class T >
topit::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template < class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
}

template < class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template < class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template < class T >
topit::Vector< T >::Vector::~Vector()
{
  delete[] data_;
}

template < class T >
void topit::Vector< T >::pushBack(const T& val)
{
  if (size_ == capacity_)
  {
    size_t newCap = (capacity_ == 0 ? 1 : capacity_ * 2);
    T* temp = new T[newCap];
    try
    {
      for (size_t i = 0; i < capacity_; ++i)
      {
        temp[i] = data_[i];
      }
    }
    catch (...)
    {
      delete[] temp;
      throw;
    }
    delete[] data_;
    data_ = temp;
    capacity_ = newCap;
  }

  data_[size_++] = val;
}

#endif
