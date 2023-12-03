#pragma once

namespace og {

template<typename T> class Vector
{
public:
  Vector() = default;
  explicit Vector(int capacity, const T &def_value);

  Vector(const Vector &);
  Vector(Vector &&) noexcept;
  Vector &operator=(const Vector &);
  Vector &operator=(Vector &&) noexcept;

  ~Vector();

  void clear();
  void resize(int capacity);
  T &at(int index);
  const T &at(int index) const;

  [[nodiscard]] int size() const;

private:
  int m_size{ 0 };
  int m_capacity{ 0 };
  int *m_data{ nullptr };
};

template<typename T>
Vector<T>::Vector(int capacity, const T &def_value)
  : m_size(capacity), m_capacity(capacity), m_data(new T[capacity])
{
  for (int i = 0; i < m_capacity; i++) { m_data[i] = def_value; }
}

template<typename T> Vector<T>::~Vector() { clear(); }

template<typename T> int Vector<T>::size() const { return m_size; }

template<typename T> T &Vector<T>::at(const int index) { return m_data[index]; }

template<typename T> const T &Vector<T>::at(const int index) const
{
  return m_data[index];
}

template<typename T> void Vector<T>::clear()
{
  if (m_data){
    delete[] m_data;
  }
  m_size = 0;
  m_capacity = 0;
}

}// namespace og
