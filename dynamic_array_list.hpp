#ifndef _DYNAMIC_ARRAY_LIST_H_
#define _DYNAMIC_ARRAY_LIST_H_

#include "abstract_list.hpp"

template <typename T>
class DynamicArrayList : public AbstractList<T>
{
public:
    // Constructor
    DynamicArrayList();

    // copy constructor
    DynamicArrayList(const DynamicArrayList& oth);

    // Destructor
    ~DynamicArrayList();

    // copy assignment
    DynamicArrayList<T>& operator=(DynamicArrayList rhs);

    //for copy-swap idiom
    void swap(DynamicArrayList<T>& x, DynamicArrayList<T>& y);

    // test if the list is empty
    bool isEmpty();

    // get the number of items in the list
    std::size_t getLength();

    // insert at position in list
    void insert(std::size_t position, const T& newEntry);

    // remove item at position
    void remove(std::size_t position);

    // clear the list (remove all entries)
    void clear();

    // get value of item at position
    T getEntry(std::size_t position);

    // set value at position
    void setEntry(std::size_t position, const T& newValue);

private:
    void resize();

    T* data;
    std::size_t maxItems;
    std::size_t length;
};

#include "dynamic_array_list.tpp"
#endif  // _DYNAMIC_ARRAY_LIST_H_
