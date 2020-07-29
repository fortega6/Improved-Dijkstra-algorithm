#include "dynamic_array_list.hpp"
#include <stdexcept>

#define ARR_BASE_SIZE 100

/**
 * @brief DynamicArrayList::resize Resize the array list to double its current size.
 */
template <typename T>
void DynamicArrayList<T>::resize()
{
    // duplicate array memory size
    if (maxItems == 0)
        maxItems = ARR_BASE_SIZE;
    else
        maxItems *= 2;

    // copy current array data to new one
    T* newArr = new  T[ maxItems ];

    for (int i = 0; i < length; ++i)
        newArr[i] = data[i];

    //release current array mem.
    //and set the new array
    delete [] data;
    data = newArr;
}

/**
 * @brief DynamicArrayList<T>::DynamicArrayList Class default constructor. Builds an
 *                                              empty list.
 */
template <typename T>
DynamicArrayList<T>::DynamicArrayList() : data(nullptr), maxItems(0), length(0)
{
}

/**
 * @brief DynamicArrayList<T>::DynamicArrayList Class copy constructor. Build a list
 *                                              from another given list.
 * @param oth   The copied list.
 */
template <typename T>
DynamicArrayList<T>::DynamicArrayList(const DynamicArrayList& oth)
{
    data = new T[ oth.maxItems ];
    for (int i = 0; i < oth.length; ++i)
        data[i] = oth.data[i];

    length = oth.length;
    maxItems = oth.maxItems;
}

/**
 * @brief DynamicArrayList<T>::~DynamicArrayList Class destructor. Release the list
 *                                               allocated memory.
 */
template <typename T>
DynamicArrayList<T>::~DynamicArrayList()
{
    delete [] data;
}

/**
 * @brief DynamicArrayList<T>::operator = Class asignment operator. Set the list to
 *                                        a copy of the right hand side given list.
 * @param rhs   Right hand side DynamicArrayList operand.
 * @return      Reference to the copy list.
 */
template <typename T>
DynamicArrayList<T>& DynamicArrayList<T>::operator=(DynamicArrayList<T> rhs)
{
    if (this != &rhs)
    {
        if (maxItems < rhs.length)    //there is no enough space in dest. list
        {
            //release current list mem.
            //and allocate enough space
            delete [] data;
            data = new T[ rhs.maxItems ];
            maxItems = rhs.maxItems;
        }

        //copy right side list
        for (int i = 0; i < rhs.length; ++i)
            data[i] = rhs.data[i];
        length = rhs.length;
    }

    return *this;
}

/**
 * @brief DynamicArrayList<T>::swap Swaps the value of two lists.
 * @param x First list.
 * @param y Second list.
 */
template <typename T>
void DynamicArrayList<T>::swap(DynamicArrayList<T>& x, DynamicArrayList<T>& y)
{
    swap(x.data, y.data);
    swap(x.length, y.length);
    swap(x.maxItems, y.maxItems);
}

/**
 * @brief DynamicArrayList<T>::isEmpty Returns whether the list is empty
 *                                     (i.e whether its size is 0).
 * @return  True if the list size is 0. False otherwise.
 */
template <typename T>
bool DynamicArrayList<T>::isEmpty()
{
    return (length == 0);
}

/**
 * @brief DynamicArrayList<T>::getLenght Returns the list size or lenght.
 *                                       The number of items in the list.
 * @return  The number of elements in the container.
 */
template <typename T>
std::size_t DynamicArrayList<T>::getLength()
{
    return length;
}

/**
 * @brief DynamicArrayList<T>::insert Insert a new item in a specific position into
 *                                    the list, using a 0-based indexing.
 *                                    Throws a std::range_error if position is invalid.
 * @param position  New Intem insert position.
 * @param newEntry  New item to insert.
 */
template <typename T>
void DynamicArrayList<T>::insert(std::size_t position, const T& newEntry)
{
    if (position < 0 || position > length)
        throw std::range_error("Range error: insert position is invalid!");

    if (length == maxItems)     //full array!
        resize();               //allocate more mem.

    //forward move array items in
    //the range [position, lenght - 1]
    for (int i = length; i > position; --i)
        data[i] = data[i - 1];

    //insert item and update array size
    data[position] = newEntry;
    ++length;
}

/**
 * @brief DynamicArrayList<T>::remove Remove a item in a specific position from
 *                                    list using a 0-based indexing. Throws a
 *                                    std::range_error if position is invalid.
 * @param position  Item to remove position.
 */
template <typename T>
void DynamicArrayList<T>::remove(std::size_t position)
{
    if (position < 0 || position >= length)
        throw std::range_error("Range error: remove position is invalid!");

    for (int i = position; i < (length - 1); ++i)
        data[i] = data[i + 1];
    --length;
}

/**
 * @brief DynamicArrayList<T>::clear Remove all item from list.
 */
template <typename T>
void DynamicArrayList<T>::clear()
{
    length = 0;
}

/**
 * @brief DynamicArrayList<T>::getEntry Return value of item at specific position
 *                                      into the list using a 0-based indexing.
 *                                      Throws a std::range_error if position is invalid.
 * @param position  The position of item to get.
 * @return          Value of item at specific position.
 */
template <typename T>
T DynamicArrayList<T>::getEntry(std::size_t position)
{
    if (position < 0 || position >= length)
        throw std::range_error("Range error: get position is invalid!");

    return data[position];
}

/**
 * @brief DynamicArrayList<T>::setEntry Set the value of item at specific position
 *                                      using a 0-based indexing. Throws a
 *                                      std::range_error if position is invalid.
 * @param position  List position to set new value.
 * @param newValue  New item value.
 */
template <typename T>
void DynamicArrayList<T>::setEntry(std::size_t position, const T& newValue)
{
    if (position < 0 || position >= length)
        throw std::range_error("Range error: set position is invalid!");

    data[position] = newValue;
}
