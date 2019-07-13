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
    T *_values;
    void copyFrom(const vector<T> &v);

public:
    vector();

    template <unsigned int SIZE>
    vector(T (&array)[SIZE]);

    // Copy
    vector(const vector<T> &v);
    vector<T> &operator=(const vector<T> &v);

    // Move
    vector<T> &operator=(vector<T> &&v);

    ~vector();

    const T &operator[](unsigned int index) const;

    unsigned int size() const;
};

template <typename T>
void vector<T>::copyFrom(const vector<T> &v)
{
    _size = v.size();
    _values = new T[_size];
    for (unsigned int i = 0; i < _size; i++)
    {
        _values[i] = v[i];
    }
}

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
    _size = SIZE;
    _values = new T[SIZE];
    for (unsigned int i = 0; i < SIZE; i++)
    {
        _values[i] = values[i];
    }
}

// Copy
template <typename T>
vector<T>::vector(const vector<T> &v)
{
    this->copyFrom(v);
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &v)
{
    // Self-assignment detection
    if (&v == this)
        return *this;

    delete _values;

    this->copyFrom(v);
    return *this;
}

// Move
template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v)
{
    // Self-assignment detection
    if (&v == this)
        return *this;

    delete _values;

    _size = v._size;
    _values = v._values;

    v._size = 0;
    v._values = __null;

    return *this;
}

template <typename T>
const T &vector<T>::operator[](unsigned int index) const
{
    return _values[index];
}

template <typename T>
unsigned int vector<T>::size() const
{
    return _size;
}

template <typename T>
vector<T>::~vector()
{
    delete[] _values;
}

} // namespace pstd

#endif