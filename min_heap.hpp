#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include "dynamic_array.hpp"

template <typename T>   // type T must be orderable (support relational operators)
class MinHeap
{
public:
     MinHeap();
     MinHeap(const MinHeap<T>& oth);
    ~MinHeap();

    MinHeap<T>& operator=(const MinHeap<T>& rhs);

    bool isEmpty();
    std::size_t numNodes();
    std::size_t height();

    T peekTop();
    void add(const T& item);
    void remove();
    void clear();

    template <typename U>
    friend void swap(MinHeap<U>& x, MinHeap<U>& y);
private:
    int parent(int node);
    int lftChild(int node);
    int rgtChild(int node);
    int minChild(int node);
    void swapNodes(int i1, int i2);

    DynamicArray<T> data_;
};

#include "min_heap.tpp"
#endif // _MIN_HEAP_H_
