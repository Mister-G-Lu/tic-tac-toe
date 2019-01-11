#ifndef DEQUE_HPP
#define DEQUE_HPP

#include "abstract_deque.hpp"
#include "DoubleNode.hpp"

#include <iostream>
#include <string>
#include <sstream>

template <typename T>
class Deque: public AbstractDeque<T>
{
private:
  DoubleNode<T>* ptrB;
  DoubleNode<T>* ptrF;
 
public:
  /** Deque constructor */
  Deque();

  /** Copy Constructor */ 
  Deque(const Deque& rhs );
  
  /** Copy assignment operator */
  Deque& operator=(Deque rhs);
  
  /** Stack destructor. Must delete any allocated memory. */
  virtual ~Deque();

  /** Returns true if the deque is empty, else false
   */
  bool isEmpty() const noexcept;

  /** Add item to the front of the deque
   * may throw std::bad_alloc
   */
  void pushFront(const T & item);

  /** Remove the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
  void popFront();

  /** Returns the item at the front of the deque
   * throws std::runtime_error if the deque is empty
   */
  T front() const;

  /** Add item to the back of the deque
   * may throw std::bad_alloc
   */
  void pushBack(const T & item);

  /** Remove the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
  void popBack();

  /** Returns the item at the back of the deque
   * throws std::runtime_error if the deque is empty
   */
  T back() const;

  /** overloaded swap for copy-swap idiom
   */
  void swap(Deque<T>& x, Deque<T>& y);

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os, const Deque<U>& d);
};

#include "deque.txx"

#endif
