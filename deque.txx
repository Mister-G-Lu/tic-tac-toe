#include <iostream>
#include <cstddef>

#include "deque.hpp"

template<typename T>
Deque<T>::Deque() : ptrB(nullptr), ptrF(nullptr)
{} // end default constructor

template<typename T>
Deque<T>::Deque(const Deque& rhs )
{
  DoubleNode<T> * ptr = rhs.ptrF; //points to node to copy
  
  if(rhs.ptrB == nullptr && rhs.ptrF == nullptr)
    {
      ptrB = nullptr;
      ptrF = nullptr;
    }
  else
    {
      //create first node and set ptrF
      ptrF = new DoubleNode<T>(ptr->getItem());

      DoubleNode<T> * cptr = ptrF; //pointer for copy of list (points to copy of node we just copied)
      ptr = ptr->getPrev(); //move to previous node (back---x---front)
      
      while(ptr != nullptr)
	{

	  cptr->setPrev(new DoubleNode<T>(ptr->getItem())); //create new node and make next (previously copied) node point to it
	  (cptr->getPrev())->setNext(cptr); //make new node point to next node
	  
	  cptr = cptr->getPrev(); //now point to new node
	  ptr = ptr->getPrev(); //move to next node in list
	}
      
      ptrB = cptr; //cptr will point to last node
    }
}

template<typename T>
Deque<T>& Deque<T>::operator=(Deque rhs)
{
  swap(*this,rhs);

  return *this;
}

template<typename T>
Deque<T>::~Deque()
{
  while(!isEmpty())
    popFront();
}

template<typename T>
bool Deque<T>::isEmpty() const noexcept
{
  return (ptrB == nullptr && ptrF == nullptr);
}

template<typename T>
void Deque<T>::pushFront(const T & item)
{
  if(isEmpty())
    {
      DoubleNode<T>* ptr = new DoubleNode<T>(item);
      ptrB = ptr;
      ptrF = ptr;
    }
  else
    {
      DoubleNode<T>* ptr = new DoubleNode<T>(item,nullptr,ptrF); //make new node point backwards
      ptrF->setNext(ptr); //previous front node should point to new node
      ptrF = ptr;
    } 
}

template<typename T>
void Deque<T>::popFront()
{
  if(isEmpty())
    throw std::runtime_error("Popping empty deque from the front");
  else if(ptrB == ptrF) //have one node in list
    {
      delete ptrF; //delete note
      
      ptrB = nullptr;
      ptrF = nullptr;
    }
  else
    {
      DoubleNode<T>* ptr = ptrF;

      ptrF = ptrF->getPrev();

      delete ptr;
    }
}

template<typename T>
T Deque<T>::front() const
{
  if(isEmpty())
    throw std::runtime_error("Looking at the front of an empty deque");
  else
    return ptrF->getItem();
}

template<typename T>
void Deque<T>::pushBack(const T & item)
{
  if(isEmpty())
    {
      DoubleNode<T>* ptr = new DoubleNode<T>(item);
      ptrB = ptr;
      ptrF = ptr;
    }
  else
    {
      DoubleNode<T>* ptr = new DoubleNode<T>(item,ptrB,nullptr); //make new node point forwards
      ptrB->setPrev(ptr); //previous front node should point to new node
      ptrB = ptr;
    } 
}

template<typename T>
void Deque<T>::popBack()
{
  if(isEmpty())
    throw std::runtime_error("Popping empty deque from the back");
  else if(ptrB == ptrF) //have one node in list
    {
      delete ptrB; //delete note
      
      ptrB = nullptr;
      ptrF = nullptr;
    }
  else
    {
      DoubleNode<T>* ptr = ptrB;

      ptrB = ptrB->getNext();

      delete ptr;
    }
}

template<typename T>
T Deque<T>::back() const
{
    if(isEmpty())
      throw std::runtime_error("Looking at the back of an empty deque");
  else
    return ptrB->getItem();

}

template<typename T>
void Deque<T>::swap(Deque<T>& x, Deque<T>& y)
{
  std::swap(x.ptrB, y.ptrB);
  std::swap(x.ptrF, y.ptrF);
  
  return;
}


template <typename U>
std::ostream& operator<<(std::ostream& os, const Deque<U>& d)
{
  DoubleNode<U> * ptr = d.ptrB;

  while(ptr != nullptr)
    {
      os << ptr->getItem() << " ";

      ptr = ptr->getNext();
    }

  return os;
}
