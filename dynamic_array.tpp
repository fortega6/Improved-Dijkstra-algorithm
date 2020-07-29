#include "dynamic_array.hpp"
#include <stdexcept>

template <typename T>
const std::size_t DynamicArray<T>::DFLT_BASE_SIZE = 100;

/**
 * @brief DynamicArray<T>::DynamicArray Array fill constructor. Builds an array of
 *                                      given size with all elements sets to given
 *                                      value. By default builds an empty (size = 0)
 *                                      array.
 * @param size  Array size.
 * @param val   Value for all elements in the array.
 */
template <typename T>
DynamicArray<T>::DynamicArray(std::size_t size, const T& val)
{
    capacity_ = (size >= DFLT_BASE_SIZE) ? 2*size : DFLT_BASE_SIZE;
    size_ = size;

    arr_ = new T[ capacity_ ];
    for (int i = 0; i < size_; ++i)
        arr_[i] = val;
}

/**
 * @brief DynamicArray<T>::DynamicArray Class copy constructor. Builds an
 *                                      array from another given array.
 * @param oth   The copied array.
 */
template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& oth)
{
    arr_ = new T[ oth.capacity_ ];

    for (int i = 0; i < oth.size_; ++i)
        arr_[i] = oth.arr_[i];

    size_ = oth.size_;
    capacity_ = oth.capacity_;
}

/**
 * @brief DynamicArray<T>::~DynamicArray Class destructor. Release the array
 *                                       allocated memory.
 */
template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete [] arr_;
}

/**
 * @brief DynamicArray<T>::operator = Class asignment operator. Set the array to
 *                                    a copy of the right hand side given array.
 * @param rhs   Right hand side DynamicArray operand.
 * @return      Reference to the copy array.
 */
template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& rhs)
{
    if (this != &rhs)
    {
        if (capacity_ < rhs.size_)    //there is no enough space in dest. list
        {
            //release current list mem.
            //and allocate enough space
            delete [] arr_;
            arr_ = new T[ rhs.capacity_ ];
            capacity_ = rhs.capacity_;
        }

        //copy right side list
        for (int i = 0; i < rhs.size_; ++i)
            arr_[i] = rhs.arr_[i];
        size_ = rhs.size_;
    }

    return *this;
}

/**
 * @brief DynamicArray<T>::isEmpty Returns whether the array is empty
 *                                 (i.e whether its size is 0).
 * @return  True if the array size is 0. False otherwise.
 */
template <typename T>
bool DynamicArray<T>::isEmpty()
{
    return (size_ == 0);
}

/**
 * @brief DynamicArray<T>::size Returns the list size or lenght.
 *                              The number of items in the array.
 * @return  The number of elements in the array.
 */
template <typename T>
std::size_t DynamicArray<T>::size()
{
    return size_;
}

/**
 * @brief DynamicArray<T>::insert Insert a new item in a specific position into
 *                                the array, using a 0-based indexing.
 *                                Throws a std::range_error if position is invalid.
 * @param pos       New Item insert position.
 * @param newEnt    New item to insert.
 */
template <typename T>
void DynamicArray<T>::insert(std::size_t pos, const T& newEnt)
{
    if (pos < 0 || pos > size_)
        throw std::range_error("Range error: insert position is invalid!");

    if (size_ == capacity_)     //full array!
        realloc();              //allocate more mem.

    //forward move array items in
    //the range [position, lenght - 1]
    for (int i = size_; i > pos; --i)
        arr_[i] = arr_[i - 1];

    //insert item and update array size
    arr_[pos] = newEnt;
    ++size_;
}

/**
 * @brief DynamicArray<T>::erase Erase the item in a specific position from
 *                               array using a 0-based indexing. Throws a
 *                               std::range_error if position is invalid.
 * @param pos  0-based position of the item to erase.
 */
template <typename T>
void DynamicArray<T>::erase(std::size_t pos)
{
    if (pos < 0 || pos >= size_)
        throw std::range_error("Range error: remove position is invalid!");

    for (int i = pos; i < (size_ - 1); ++i)
        arr_[i] = arr_[i + 1];
    --size_;
}

/**
 * @brief DynamicArray<T>::pushBack Add a new item at the end of array.
 * @param newEnt    Value of item added.
 */
template <typename T>
void DynamicArray<T>::pushBack(const T& newEnt)
{
    insert(size_, newEnt);
}

/**
 * @brief DynamicArray<T>::popBack Erase the item at the end of array.
 */
template <typename T>
void DynamicArray<T>::popBack()
{
    erase(size_ - 1);
}

/**
 * @brief DynamicArray<T>::at   Returns a reference to the item at position idx
 *                              of array. Throws a std::range_error if position
 *                              is invalid.
 * @param idx   Position of an item in the array.
 * @return      Reference to the array item in the position idx.
 */
template <typename T>
T& DynamicArray<T>::at(std::size_t idx)
{
    if (idx >= size_)
        throw std::range_error("Range error: Invalid array index");

    return arr_[idx];
}

/**
 * @brief DynamicArray<T>::operator []  Returns a reference to the item at position
 *                                      idx of array.
 * @param idx   Position of an item in the array.
 * @return      Reference to the array item in the position idx.
 */
template <typename T>
T& DynamicArray<T>::operator[](size_t idx)
{
    return arr_[idx];
}

/**
 * @brief DynamicArray<T>::clear Erase all item from array.
 */
template <typename T>
void DynamicArray<T>::clear()
{
    size_ = 0;
}

/**
 * @brief swap Swaps the value of two array.
 * @param x First array to the swapping.
 * @param y Second array to the swapping.
 */
template <typename U>
void swap(DynamicArray<U>& x, DynamicArray<U>& y)
{
    swap(x.arr_, y.arr_);
    swap(x.size_, y.size_);
    swap(x.capacity_, y.capacity_);
}

/**
 * @brief DynamicArray<T>::realloc Resize the array to double its current capacity.
 */
template <typename T>
void DynamicArray<T>::realloc()
{
    // copy current array data to new one
    capacity_ *= 2;
    T* newArr = new  T[ capacity_ ];

    for (int i = 0; i < size_; ++i)
        newArr[i] = arr_[i];

    //release current array mem.
    //and set the new array
    delete [] arr_;
    arr_ = newArr;
}
