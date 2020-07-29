#include "heap_priority_queue.hpp"

/**
 * @brief HeapPriorityQueue<T>::HeapPriorityQueue Default class constructor. Builds
 *                                                an empty priority queue.
 */
template <typename T>
HeapPriorityQueue<T>::HeapPriorityQueue() {}

/**
 * @brief HeapPriorityQueue<T>::HeapPriorityQueue Class copy constructor. Builds a
 *                                                HeapPriorityQueue as copy of another
 *                                                given HeapPriorityQueue.
 * @param oth   HeapPriorityQueue to copy.
 */
template <typename T>
HeapPriorityQueue<T>::HeapPriorityQueue(const HeapPriorityQueue<T>& oth) : itemHeap_(oth.itemHeap_)
{
}

/**
 * @brief HeapPriorityQueue<T>::~HeapPriorityQueue Class destructor.
 */
template <typename T>
HeapPriorityQueue<T>::~HeapPriorityQueue() {}

/**
 * @brief HeapPriorityQueue<T>::operator = HeapPriorityQueue assignment operator.
 *                                         Sets this HeapPriorityQueue to be a copy
 *                                         of the right hand side HeapPriorityQueue.
 * @param rhs   Right hand side HeapPriorityQueue operand.
 * @return      Reference to the copy HeapPriorityQueue.
 */
template <typename T>
HeapPriorityQueue<T>& HeapPriorityQueue<T>::operator=(const HeapPriorityQueue<T>& rhs)
{
    if (this != &rhs)
        itemHeap_ = rhs.itemHeap_;

    return *this;
}

/**
 * @brief HeapPriorityQueue<T>::isEmpty Returns whether queue is empty, i.e whether
 *                                      there are no items in the queue.
 * @return  True if there are no items in the queue. False otherwise.
 */
template <typename T>
bool HeapPriorityQueue<T>::isEmpty()
{
    return itemHeap_.isEmpty();
}

/**
 * @brief HeapPriorityQueue<T>::add Adds a new item into the queue, placing it in
 *                                  the appropiate position.
 * @param item  New item to add to the queue.
 */
template <typename T>
void HeapPriorityQueue<T>::add(const T& item)
{
    itemHeap_.add(item);
}

/**
 * @brief HeapPriorityQueue<T>::remove Removes the lowest priority item from the queue.
 *                                     Throws a std::logic_error if queue is empty.
 */
template <typename T>
void HeapPriorityQueue<T>::remove()
{
    if (itemHeap_.isEmpty())
        throw std::logic_error("Logic error: removing items from a empty queue!");

    itemHeap_.remove();
}

/**
 * @brief HeapPriorityQueue<T>::peek Returns the item with the lowest priority from
 *                                   the queue. Throws a std::logic_error if the queue
 *                                   is empty.
 * @return Value of the item with lowest priority in the queue.
 */
template <typename T>
T HeapPriorityQueue<T>::peek()
{
    if (itemHeap_.isEmpty())
        throw std::logic_error("Logic error: removing items from a empty queue!");

    return itemHeap_.peekTop();
}

/**
 * @brief HeapPriorityQueue<T>::clear Removes all items from the queue.
 */
template <typename T>
void HeapPriorityQueue<T>::clear()
{
    itemHeap_.clear();
}

/**
 * @brief swap Swap the value of two HeapPriorityQueues.
 * @param x First HeapPriorityQueues to the swapping.
 * @param y Second HeapPriorityQueues to the swapping.
 */
template <typename U>
void swap(HeapPriorityQueue<U>& x, HeapPriorityQueue<U>& y)
{
    swap(x.itemHeap_, y.itemHeap_);
}
