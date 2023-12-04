#pragma once

#include <cstddef>

namespace og {

/*** Definition ***/

template<typename T> class Vector
{
public:
  Vector() = default;
  explicit Vector(size_t capacity, const T &def_value);

  Vector(const Vector &);
  Vector(Vector &&) noexcept;
  Vector &operator=(const Vector &);
  Vector &operator=(Vector &&) noexcept;

  ~Vector();

  void clear();
  void resize(const size_t capacity);
  T &at(size_t index);
  const T &at(size_t index) const;

  [[nodiscard]] size_t size() const;

private:
  size_t m_size{ 0 };
  size_t m_capacity{ 0 };
  T *m_data{ nullptr };
};

/*** Implementation ***/

template<typename T>
Vector<T>::Vector(size_t capacity, const T &def_value)
  : m_size(capacity), m_capacity(capacity), m_data(new T[capacity])
{
  for (size_t i = 0; i < m_capacity; i++) { m_data[i] = def_value; }
}

template<typename T> Vector<T>::~Vector() { clear(); }

template<typename T> size_t Vector<T>::size() const { return m_size; }

template<typename T> T &Vector<T>::at(const size_t index)
{
  return m_data[index];
}

template<typename T> const T &Vector<T>::at(const size_t index) const
{
  return m_data[index];
}

template<typename T> void Vector<T>::resize(const size_t capacity)
{
  // T *new_data = new T[capacity];
  // for (size_t i = 0; i < capacity; i++) {
  //   if (i == m_size) { break; }
  //   new_data[i] = m_data[i];
  // }
  // m_data = new_data;
  //
}

template<typename T> void Vector<T>::clear()
{
  delete[] m_data;
  m_data = nullptr;
  m_size = 0;
  m_capacity = 0;
}

}// namespace og
