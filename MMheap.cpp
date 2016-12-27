/*
 * File:    MMheap.cpp
 * Author:  Federico Cifuentes-Urtubey
 * Date:    4/15/16
 *
 * Implementation of the MMheap class.
 */

#ifndef MMHEAP_CPP
#define MMHEAP_CPP

#include "MMheap.h"

template <class T>
MMheap<T>::MMheap() : m_size(0), m_maxLevel(0)
{
  // Insert dummy obj into vector[0] for easy parent/child indexing 
  T dummy;
  m_heap.push_back(dummy);
}

template <class T>
MMheap<T>::~MMheap()
{
  m_size = 0;
  m_maxLevel = 0;
  m_heap.clear();
}

template <class T>
int MMheap<T>::size() const
{
  return m_size;
}

template <class T>
void MMheap<T>::dump()
{ 
  if (m_size == 0)
    throw MyException("Dump: The heap has no data from being empty.");
  
  cout << "--- min-max heap dump ---" << endl
       << "  Size = " << size() << endl
       << "  Minimum = " << getMin() << endl
       << "  Maximum = " << getMax() << endl;
  
  // Cases: Odd levels, even levels
  if (m_maxLevel % 2 == 1)
    cout << "  Last level is odd \n";
  else
    cout << "  Last level is even \n";

  cout << "--- heap data items --- \n";
  
  // Prints out items in the heap
  for (int i = 1; i <= m_size; ++i)
    cout << "H[" << i << "] = " << m_heap[i] << endl;
}

template <class T>
void MMheap<T>::insert(T x)
{
  // The new item will be at index [m_size]
  m_heap.push_back(x);
  m_size++;
  
  calculateLevels();  
  percolateUp(m_size);
}

template <class T>
T MMheap<T>::getMin() const
{
  if (m_size == 0)
    throw MyException("Get Min: There is no minimum in an empty heap");
  
  // The min value in a min-max heap is the root
  return m_heap[1];
}

template <class T>
T MMheap<T>::getMax() const
{
  if (m_size == 0)
    throw MyException("Get Max: There is no maximum in an empty heap");
  
  if (m_size == 1)
    return m_heap[1];
  else if (m_size == 2)
    return m_heap[2];
  else
  {
    // The max val in a min-max heap will be one of the root's children
    if (m_heap[2] < m_heap[3])
      return m_heap[3];
    else
      return m_heap[2];
  }
}

template <class T>
T MMheap<T>::deleteMin()
{
  if (m_size == 0)
    throw MyException("Delete min: There is no minimum in an empty heap");

  // Swap min item with rightmost leaf
  T min = getMin();
  m_heap[1] = m_heap[m_size];
  m_size--;
  
  // Delete the index of where the last leaf was to correct vector sizing
  m_heap.pop_back();
  
  calculateLevels();

  // Fixes the heap (only if there is at least 1 item in the heap)
  if (m_size > 0)
    trickleDown(1);
  
  return min;
}

template <class T>
T MMheap<T>::deleteMax()
{
  if (m_size == 0)
    throw MyException("Delete max: There is no maximum in an empty heap");
  
  T max = getMax();
  int index_of_max_val = 0;
  
  // Find the index of the max item in the heap
  if (m_size == 1) 
    index_of_max_val = 1;
  else if (m_size == 2) 
    index_of_max_val = 2;
  else 
    index_of_max_val = (m_heap[2] < m_heap[3]) ? 3 : 2;
  
  // Bring the last leaf up to the max item's index
  m_heap[index_of_max_val] = m_heap[m_size];
  m_size--;
  
  // Delete the index of where the last leaf was to correct vector sizing
  m_heap.pop_back();
  
  calculateLevels();
  
  // Fix the heap
  if (m_size > 0)
    trickleDown(index_of_max_val);
  
  return max;
}

template <class T>
int MMheap<T>::getLevels() const
{
  return m_maxLevel;
}

template <class T>
void MMheap<T>::calculateLevels()
{
  if (m_size == 0)
    m_maxLevel = 0;

  else
  {
    int levels = 0, numNodes = m_size;
 
    // Adds 1 level until it reaches the root
    while (numNodes != 1){
      numNodes /= 2;
      levels++;
    }
    
    m_maxLevel = levels;
  }
}

template <class T>
void MMheap<T>::trickleDown(int x)
{
  // If x is on a min level, call trickleDownMin; else, trickleDownMax
  int xLevel = (int)log2(x) % 2;
  if (xLevel == 0)
    trickleDownMin(x);
  else
    trickleDownMax(x);
}

template <class T>
void MMheap<T>::trickleDownMin(int index)
{
  // Check if m_heap[index] has children
  // if is has none, it doesn't have to trickle down 
  if ((index * 2) <= m_size)
  {
    /* Find the smallest child, defaulted to the left child */
    int smallestChildIndex = index * 2;
    T leftChild = m_heap[index * 2];

    // Check if the right child, if it exists, is smaller than the left
    if ( (index * 2) + 1 <= m_size )
    {
      T rightChild = m_heap[(index * 2) + 1];
      
      if ( rightChild < leftChild )
	smallestChildIndex = (index * 2) + 1;
      
      // This IF block finds the smallest grandchild, if any
      if ((index * 4) <= m_size)
      {
	int smallestGChildIndex = index * 4;
	
	for (int i = index * 4; (i < (index * 4) + 4) && (i <= m_size); ++i)
	  if ( m_heap[i] < m_heap[smallestGChildIndex] )
	    smallestGChildIndex = i;
	
	if ( m_heap[smallestGChildIndex] < m_heap[smallestChildIndex] )
	  smallestChildIndex = smallestGChildIndex;
      }
    }
    
    /* At this point, the smallest child/grandchild has been found */

    // If the smallest item is a grandchild, the swap is complex...
    if ( smallestChildIndex <= m_size && smallestChildIndex >= (index *4) )
    {  
      if ( m_heap[smallestChildIndex] < m_heap[index] )
      {
	T temp = m_heap[index];
	m_heap[index] = m_heap[smallestChildIndex];
	m_heap[smallestChildIndex] = temp;

	// m_heap[smallestChildIndex] is the original item we wanted to move
	// swap with parent if it's smaller to maintain Min-level property
	if ( m_heap[smallestChildIndex / 2] < m_heap[smallestChildIndex] )
	{
	  T tmp = m_heap[smallestChildIndex];
	  m_heap[smallestChildIndex] = m_heap[smallestChildIndex / 2];
	  m_heap[smallestChildIndex / 2] = tmp;
	} 
	
	trickleDownMin(smallestChildIndex);
      }
    }
    
    // Else, the smallest item is a child, swap if m_heap[index] is greater
    else
    {
      if ( m_heap[smallestChildIndex] < m_heap[index] )
      {
	      T temp = m_heap[index];
        m_heap[index] = m_heap[smallestChildIndex];
        m_heap[smallestChildIndex] = temp;
      }
    }

  }
}

template <class T>
void MMheap<T>::trickleDownMax(int index)
{
  // Check if m_heap[index] has children
  // if is has none, it doesn't have to trickle down 
  if ((index * 2) <= m_size)
  {
    /* Find the largest child, defaulted to the left one */
    int largestIndex = index * 2;
    T leftChild = m_heap[index * 2];

    // Check if the right child, if it exists, is larger than the left
    if ( (index * 2) + 1 <= m_size )
    {
      T rightChild = m_heap[(index * 2) + 1];
      
      if ( leftChild < rightChild )
	largestIndex = (index * 2) + 1;

      /* Both children have been checked at this point */
      
      // This IF block finds the smallest grandchild, if any
      if ((index * 4) <= m_size)
      {
	int biggestGChildIndex = index * 4;
	
	for (int i = index * 4; (i < (index * 4) + 4) && (i <= m_size); ++i)
	  if ( m_heap[biggestGChildIndex] < m_heap[i] )
	    biggestGChildIndex = i;
	
	if ( m_heap[largestIndex] < m_heap[biggestGChildIndex] )
	  largestIndex = biggestGChildIndex;
      }
    }
    
    /* At this point, the largest child/grandchild has been found */

    // If the largest item is a grandchild, the swap is complex...
    if ( largestIndex >= (index * 4) )
    {  
      if ( m_heap[index] < m_heap[largestIndex] )
      {
	T temp = m_heap[index];
	m_heap[index] = m_heap[largestIndex];
	m_heap[largestIndex] = temp;

	// m_heap[largestIndex] is the original item we want to move, but
	// it has to be larger than or equal to the parent; swap if it's not
	if ( m_heap[largestIndex] < m_heap[largestIndex / 2] )
	{
	  T tmp = m_heap[largestIndex / 2];
	  m_heap[largestIndex / 2] = m_heap[largestIndex];
	  m_heap[largestIndex] = tmp;
	} 
	
	trickleDownMax(largestIndex);
      }
    }
    
    // Else, the smallest item is a child, swap if m_heap[index] is greater
    else
    {
      if ( m_heap[largestIndex] > m_heap[index] )
      {
	T temp = m_heap[index];
        m_heap[index] = m_heap[largestIndex];
        m_heap[largestIndex] = temp;
      }
    }

  }
}

template <class T>
void MMheap<T>::percolateUp(int x)
{
  // int to find the index to switch with
  int newIndex = 0;
  
  // Find out if the current index is at a min or max level
  int currLevel = (int)log2(x) % 2; 
  
  // If at a min level, switch with grandparent; else switch with parent
  if (currLevel == 0)
    newIndex = x / 4;
  else
    newIndex = x / 2;
  
  // Checks for valid index and if the index to swap with is greater
  if ( (newIndex > 0) && (m_heap[x] < m_heap[newIndex]) )
  {
    T temp = m_heap[newIndex];
    m_heap[newIndex] = m_heap[x];
    m_heap[x] = temp;
    percolateUp(newIndex);      
  }
  
  /* All the code below does a second check to maintain heap properties */
  if (currLevel == 1)
    newIndex = x / 4;
  else
    newIndex = x / 2;

  // Checks for valid index and if the index to swap with is less
  if ( (newIndex > 0) && (m_heap[newIndex] < m_heap[x]) )
  {
    T temp = m_heap[newIndex];
    m_heap[newIndex] = m_heap[x];
    m_heap[x] = temp;
    percolateUp(newIndex);
  }
}

#endif