#ifndef _DYNAMIC_ARRAY_H_
#define _DYNAMIC_ARRAY_H_

#include <cstddef>

template <typename T>
class DynamicArray
{
public:
     DynamicArray(std::size_t size = 0, const T& val = T());
     DynamicArray(const DynamicArray& oth);
    ~DynamicArray();

    DynamicArray<T>& operator=(const DynamicArray& rhs);

    std::size_t size();
    bool isEmpty();

    void insert(std::size_t pos, const T& newEnt);
    void erase(std::size_t pos);
    void pushBack(const T& newEnt);
    void popBack();

    T& at(std::size_t idx);
    T& operator[](std::size_t idx);

    void clear();

    template <typename U>
    friend void swap(DynamicArray<U>& x, DynamicArray<U>& y);
private:
    void realloc();

    static const std::size_t DFLT_BASE_SIZE;

    T* arr_;
    std::size_t size_;
    std::size_t capacity_;
};

#include "dynamic_array.tpp"
#endif  // _DYNAMIC_ARRAY_H_
