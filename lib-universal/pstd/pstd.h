// Some ported (or partially ported) stuff from std

#ifndef PSTD_H
#define PSTD_H

namespace pstd
{

template <typename T>
class vector
{
private:
    // T values;
    unsigned int _size;
    T * _values;

public: 
    vector();
    template <unsigned int SIZE>
    vector(T (&array)[SIZE]);
    const T & operator[](unsigned int index) const;

    unsigned int size() const;
};

template <typename T>
vector<T>::vector()
{
  _values = NULL;
  _size = 0;
}

template <typename T>
template <unsigned int SIZE>
vector<T>::vector(T (&values)[SIZE])
{
    _values = values;
    _size = SIZE;
}

template <typename T>
const T & vector<T>::operator[](unsigned int index) const
{
  return _values[index];
}

template <typename T>
unsigned int vector<T>::size() const
{
  return _size;
}

} // namespace pstd

#endif