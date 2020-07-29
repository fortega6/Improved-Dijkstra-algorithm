#ifndef _HEAP_PRIORITY_QUEUE_H
#define _HEAP_PRIORITY_QUEUE_H

#include "abstract_priority_queue.hpp"
#include "min_heap.hpp"

template <typename T>
class HeapPriorityQueue : public AbstractPriorityQueue<T>
{
public:
    HeapPriorityQueue();
    HeapPriorityQueue(const HeapPriorityQueue<T>& oth);
   ~HeapPriorityQueue();

    HeapPriorityQueue<T>& operator=(const HeapPriorityQueue<T>& rhs);

    bool isEmpty();
    void add(const T& item);
    void remove();
    T peek();
    void clear();

    template<typename U>
    friend void swap(MinHeap<U>& x, MinHeap<U>& y);

private:
    MinHeap<T> itemHeap_;
};

#include "heap_priority_queue.tpp"
#endif  // _HEAP_PRIORITY_QUEUE_H
