/*
 * File:    MMheap.h
 * Author:  Federico Cifuentes-Urtubey
 * Date:    4/15/16
 *
 * Definition of the MMheap class, a data 
 * structure to represent a min-max heap
 */

#ifndef MMHEAP_H
#define MMHEAP_H

#include "MyException.h" // <iostream>, <string>
#include <vector>
#include <math.h>

using namespace std;

template <class T>
class MMheap
{
  public:
  
    /* MMHeap() - default constructor
     * pre - none
     * post - constructs an MMHeap obj with size 0
     */
    MMheap();

    /* ~MMHeap() - destructor
     * pre - none
     * post - destructs an MMHeap obj
     */
    ~MMheap();

    /* size()
     * pre - none
     * post - returns the number of items in the min-max heap
     */
    int size() const;
    
    /* dump()
     * pre - none
     * post - prints out the contents of the min-max heap
     */
    void dump();
    
    /* insert()
     * pre - pass in a value to insert 
     * post - inserts the element into the heap (duplicates are accepted)
     */
    void insert(T x); 

    /* getMin()
     * pre - none
     * post - returns the smallest value of the heap
     */
    T getMin() const;
    
    /* getMax()
     * pre - none
     * post - returns the largest value of the heap
     */
    T getMax() const;    

    /* deleteMin()
     * pre - none
     * post - removes and returns the smallest item
     */
    T deleteMin();
    
    /* deleteMax()
     * pre - none
     * post - removes and returns the largest item
     */
    T deleteMax();

    /* getLevels()
     * pre - none
     * post - returns the height of the heap
     */
    int getLevels() const;

    /* calculateLevels()
     * pre - none
     * post - after every insertion/deletion, this reassigns the number of
     *    levels in the heap by percolating up by index
     */
    void calculateLevels();
    
    /* percolateDown()
     * pre - pass in the index of the item to shift down the heap
     * post - fixes the heap to maintain heap properties
     */
    void trickleDown(int x);

    /* trickleDownMin()
     * pre - pass in the index of an item
     * post - fixes the heap for an item at a Min level
     */
    void trickleDownMin(int index);

    /* trickleDownMax()
     * pre - pass in the index of an item
     * post - fixes the heap for an item at a Max level
     */
    void trickleDownMax(int index);
    
    /* percolateUp()
     * pre - pass in the index of the item to shift up the heap
     * post - fixes the heap to maintain heap properties
     */
    void percolateUp(int x);

  private:
    int m_size;       // Number of elements in the heap
    int m_maxLevel;   // Height of the heap (0, 1, 2...)
    vector<T> m_heap; // Elements of the heap
};

#include "MMheap.cpp"

#endif