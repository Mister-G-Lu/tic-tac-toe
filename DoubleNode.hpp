#ifndef DOUBLE_NODE_HPP
#define DOUBLE_NODE_HPP

template<typename ItemType>
class DoubleNode
{
private: 
  ItemType item; // A data item 
  DoubleNode <ItemType>* next; // Pointer to next node 
  DoubleNode <ItemType>* prev; // Pointer to previous node
public: 
  DoubleNode();
  DoubleNode(const ItemType& anItem);
  DoubleNode(const ItemType& anItem, DoubleNode <ItemType>* nextNodePtr, DoubleNode <ItemType>* prevNodePtr); 
  void setItem(const ItemType& anItem);
  void setNext(DoubleNode <ItemType>* nextNodePtr);
  void setPrev(DoubleNode <ItemType>* prevNodePtr);
  ItemType getItem() const;
  DoubleNode<ItemType>* getNext() const;
  DoubleNode<ItemType>* getPrev() const;
};

#include "DoubleNode.txx"

#endif
