#include "min_heap.hpp"
#include <cmath>

//#include <iostream> //debug

/**
 * @brief MinHeap::MinHeap MinHeap default constructor. Builds an empty MinHeap.
 */
template <typename T>
MinHeap<T>::MinHeap()
{
}

/**
 * @brief MinHeap<T>::MinHeap MinHeap copy constructor. Builds a MinHeap as the copy
 *                            of another given MinHeap.
 * @param oth   The MinHeap to copy.
 */
template <typename T>
MinHeap<T>::MinHeap(const MinHeap<T>& oth) : data_(oth.data_)
{
}

/**
 * @brief MinHeap<T>::~MinHeap MinHeap class destructor.
 */
template <typename T>
MinHeap<T>::~MinHeap()
{
}

/**
 * @brief MinHeap<T>::operator = MinHeap copy asignment operator. Set the MinHeap as
 *                               a copy of right hand side operand.
 * @param rhs   Right hand side MinHeap operand.
 * @return      Reference to copy MinHeap.
 */
template <typename T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T>& rhs)
{
    if (this != &rhs)
        data_ = rhs.data_;

    return *this;
}

/**
 * @brief MinHeap<T>::isEmpty   Returns whether the min. heap is empty (i.e whether
 *                              the nodes numbers is equal to 0).
 * @return  True if the nodes number into the min. heap is 0. False otherwise.
 */
template <typename T>
bool MinHeap<T>::isEmpty()
{
    return data_.isEmpty();
}

/**
 * @brief MinHeap<T>::numNodes  Returns the number of nodes into the heap.
 * @return The numbers of nodes into the heap.
 */
template <typename T>
std::size_t MinHeap<T>::numNodes()
{
    return data_.size();
}

/**
 * @brief MinHeap<T>::height    Returns the number of levels in the heap.
 * @return The number of levels in the heap.
 */
template <typename T>
std::size_t MinHeap<T>::height()
{
    return size_t(std::log2(data_.size() + 1));
}

/**
 * @brief MinHeap<T>::peekTop   Return the value of the top node into the heap.
 * @return  Value of the top node into the heap.
 */
template <typename T>
T MinHeap<T>::peekTop()
{
    return data_[0];
}

/**
 * @brief MinHeap<T>::add Add a new item to, and reorganize the heap.
 * @param item  New item to add.
 */
template <typename T>
void MinHeap<T>::add(const T& item)
{
    data_.pushBack(item);

    int inode = data_.size() - 1;
    int parnt = parent(inode);

    while (inode > 0 && data_[inode] < data_[parnt])
    {
        swapNodes(inode, parnt);
        inode = parnt;
        parnt = parent(parnt);
    }
}

/**
 * @brief MinHeap<T>::remove Removes the top node from, and reorganizes, the heap.
 */
template <typename T>
void MinHeap<T>::remove()
{
    if (data_.size() == 0)
        return;

    swapNodes(0, data_.size() - 1); //swap root and last nodes
    data_.popBack();                //remove last node (old root value)

    //reorganize the heap
    int inode = 0;
    int minCh = minChild(inode);

    while (minCh != -1 && data_[inode] > data_[minCh])
    {
        swapNodes(inode, minCh);
        inode = minCh;
        minCh = minChild(minCh);
    }
}

/**
 * @brief MinHeap<T>::clear Removes all nodes in the heap.
 */
template <typename T>
void MinHeap<T>::clear()
{
    data_.clear();
}

/**
 * @brief MinHeap<T>::swap Swap the value of two MinHeaps.
 * @param x First MinHeap to the swapping.
 * @param y Second MinHeap to the swapping.
 */
template <typename U>
void swap(MinHeap<U>& x, MinHeap<U>& y)
{
    swap(x.data_, y.data_);
}

/**
 * @brief MinHeap<T>::parent    Returns the index of the parent of node.
 * @param i 0-based index of a node in the heap.
 * @return  0-based index of the parent of node. -1 if the node does not
 *          exist or its the root node.
 */
template <typename T>
int MinHeap<T>::parent(int node)
{
    return (node < 1 || node >= data_.size()) ? -1 : (node - 1)/2;
}

/**
 * @brief MinHeap<T>::lftChild  Returns the index of left child of node.
 * @param i 0-based index of a node in the heap.
 * @return  0-based index of the left child of node.
 *          -1 if the node does not exist or its a leaf node.
 */
template <typename T>
int MinHeap<T>::lftChild(int node)
{
    return (node < 0 || (2*node + 1) >= data_.size()) ? -1 : 2*node + 1;
}

/**
 * @brief MinHeap<T>::rgtChild  Returns the index of right child of node.
 * @param i 0-based index of a node in the heap.
 * @return  0-based index of the right child of node.
 *          -1 if the node does not exists or its a leaf node.
 */
template <typename T>
int MinHeap<T>::rgtChild(int node)
{
    return (node < 0 || (2*node + 2) >= data_.size()) ? -1 : 2*node + 2;
}

/**
 * @brief MinHeap<T>::minChild  Returns the index of the minimun value child of node.
 * @param node  0-based index of a node in the heap.
 * @return      0-based index of minimun value child node. -1 if node does not exist
 *              or its a leaf node.
 */
template <typename T>
int MinHeap<T>::minChild(int node)
{
    int lftCh = lftChild(node);
    int rgtCh = rgtChild(node);

    int min;
    if (lftCh != -1)
        if (rgtCh != -1)
            min = (data_[lftCh] < data_[rgtCh]) ? lftCh : rgtCh;
        else
            min = lftCh;
    else
        min = -1;

    return min;
}

/**
 * @brief MinHeap<T>::swapNodes Swap the value of two nodes in the heap.
 * @param i1    0-based index for first node.
 * @param i2    0-based index for second node.
 */
template <typename T>
void MinHeap<T>::swapNodes(int i1, int i2)
{
    T val1 = data_.at(i1);
    T val2 = data_.at(i2);

    data_[i1] = val2;
    data_[i2] = val1;
}
