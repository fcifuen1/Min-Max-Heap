/*
 * File:    tree2_driver.cpp
 * Author:  Federico Cifuentes-Urtubey
 * Date:    4/24/16
 * 
 * Test driver for tree2.txt
 */

#include "MMheap.h"      // <vector>, <math.h>, using namespace std
#include "MyException.h" // <iostream>, <string>

#include <fstream>
#include <cstdlib>

int main(int argc, char* argv[])
{
  MMheap<float> heap;
  MMheap<int>* ptrHeap = new MMheap<int>;
  vector<float> numbers;
  string filename;
  
  cout << argv[0] << " " << argv[1] << "\n";
  
  if(argc == 2)
    filename = argv[1];
  else
  {
    cout << "Not enough command line arguments." << endl;
    return 0;
  }
  
  ifstream file(filename.c_str());

  if (file.is_open())
  {
    string line;
    
    while(getline(file, line))
      numbers.push_back( atof(line.c_str()) );
    
    file.close();
  }
  else
  {
    cout << "File was not opened." << endl;
    return 0;
  }

  cout << "*** Attempt to get the max and min from ptrHeap (empty) ***\n";
  cout << "--------------------" << endl;
  
  try { ptrHeap->getMax(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  try { ptrHeap->getMin(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  cout << endl;

  
  cout << "*** Inserting 7, 64, 42 into ptrHeap ***" << endl;
  cout << "--------------------" << endl;
  ptrHeap->insert(7);
  ptrHeap->insert(64);
  ptrHeap->insert(42);
  ptrHeap->dump();
  
  cout << "--------------------" << endl;
  cout << "*** Then deleteMax. ***" << endl;
  cout << "--------------------" << endl;

  ptrHeap->deleteMax();
  ptrHeap->dump();
  
  
  cout << "--------------------" << endl;
  cout << "*** Attempt to dump 'heap' (empty) " << endl;
  cout << "--------------------" << endl;

  try { heap.dump(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  cout << "--------------------" << endl;
  cout << "*** Make the min-max heap from tree2.txt ***" << endl;
  cout << "--------------------" << endl;
  
  for (unsigned int i = 0; i < numbers.size(); ++i){
    heap.insert(numbers[i]);
    //cout << "INSERTED " << numbers[i] << endl;
  }
  
  heap.dump();
  
  cout << "--------------------" << endl;
  cout << "*** Then insert 16, 17 into 'heap' ***" << endl;
  cout << "--------------------" << endl;

  // This shouldn't cause any shifting in the heap
  heap.insert(16.0f);
  heap.insert(17.0f);
  heap.dump();

  
  cout << "--------------------" << endl;
  cout << "*** Then call deleteMin 2 times. ***" << endl;
  cout << "--------------------" << endl;

  // Shouldn't cause exceptions
  try {
    heap.deleteMin();
    heap.deleteMin();
    heap.dump();
  }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  cout << "--------------------" << endl;
  cout << "*** Then call deleteMax 3 times. ***"<<endl;
  cout << "--------------------" << endl;

  // Shouldn't cause exceptions
  try {
    heap.deleteMax();
    heap.deleteMax();
    heap.deleteMax();
    heap.dump();
  }
  catch (MyException &E) { cout << E.getMessage() << endl; }

  cout << "--------------------" << endl;
  
  delete ptrHeap;
  
  return 0;
}
