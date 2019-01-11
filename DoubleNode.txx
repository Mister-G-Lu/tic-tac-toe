#include "DoubleNode.hpp"
template <typename ItemType>
DoubleNode<ItemType>::DoubleNode() {}
template <typename ItemType>
DoubleNode<ItemType>::DoubleNode(const ItemType& anItem)
{
    item = anItem;
    next = nullptr;
    prev = nullptr;
}
template <typename ItemType>
DoubleNode<ItemType>::DoubleNode(const ItemType& anItem, DoubleNode <ItemType>* nextNodePtr, DoubleNode <ItemType>* prevNodePtr)
{
    item = anItem;
    next = nextNodePtr;
    prev = prevNodePtr;
}
template <typename ItemType>
void DoubleNode<ItemType>::setItem(const ItemType& anItem)
{
    item = anItem;
}

template <typename ItemType>
void DoubleNode<ItemType>::setNext(DoubleNode <ItemType>* nextNodePtr)
{
    next = nextNodePtr;
}
template <typename ItemType>
void DoubleNode<ItemType>::setPrev(DoubleNode <ItemType>* prevNodePtr)
{
    prev = prevNodePtr;
}
template <typename ItemType>
ItemType DoubleNode<ItemType>::getItem() const
{
    return item;
}
template <typename ItemType>
DoubleNode<ItemType>* DoubleNode<ItemType>::getNext() const
{
    return next;
}
template <typename ItemType>
DoubleNode<ItemType>* DoubleNode<ItemType>::getPrev() const
{
    return prev;
}
