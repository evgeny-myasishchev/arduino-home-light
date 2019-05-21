// Some ported (or partially ported) stuff from std

#ifndef PSTD_H
#define PSTD_H

#include <stdarg.h>

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

    vector(unsigned int size, ...);

    const T & operator[](unsigned int index) const;

    unsigned int size() const;
};

template <typename T>
vector<T>::vector()
{
  _values = __null;
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
vector<T>::vector(unsigned int size, ...)
{
    va_list args;
    va_start(args,size);
    _size = size;
    T values[size];
    for(unsigned int i = 0; i < size; i++) {
      values[i] = va_arg(args,T);
    }
    va_end(args);
    _values = values;
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