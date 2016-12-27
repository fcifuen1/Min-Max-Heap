/*
 * File:    Driver.cpp
 * Author:  Federico Cifuentes-Urtubey
 * Date:    4/24/16
 *
 * Test driver for test.txt 
 */

#include "MyException.h" // <iostream>, <string>
#include "MMheap.h"      // <vector>, <math.h>, using namespace std

#include <fstream>
#include <cstdlib>

int main(int argc, char *argv[])
{
  MMheap<int> theHeap;
  MMheap<float>* fPtrHeap = new MMheap<float>;
  MMheap<double>* dPtrHeap = new MMheap<double>;
  
  vector<int> intNums;
  vector<double> dNums;

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
    {
      intNums.push_back( atoi(line.c_str()) );
      dNums.push_back( atof(line.c_str()) );
    }
    
    file.close();
  }
  else
  {
    cout << "File was not opened." << endl;
    return 0;
  }

  cout << "*** Insert 18, 94, 74. ***" << endl;
  cout << "--------------------" << endl;
  fPtrHeap->insert(18.0f);
  fPtrHeap->insert(94.0f);
  fPtrHeap->insert(74.0f);
  fPtrHeap->dump();

  cout << "--------------------" << endl;
  cout << "*** Then deleteMax. ***" << endl;
  cout << "--------------------" << endl;

  try {
    fPtrHeap->deleteMax();
    fPtrHeap->dump();
  }
  catch (MyException &E) { cout << E.getMessage() << endl; }

  cout << "--------------------" << endl;
  cout << "*** Make the min-max heap in Figure 6.57. ***" << endl;
  cout << "--------------------" << endl;

  // Should cause the dump() exception
  try { theHeap.dump(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  for (unsigned int i = 0; i < intNums.size(); ++i)
    theHeap.insert(intNums[i]);
  
  try { theHeap.dump(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
    
  cout << "--------------------" << endl;
  cout << "*** Then insert 53, 57, 13, 12, 9, 10. ***" << endl;
  cout << "--------------------" << endl;

  theHeap.insert(53);
  theHeap.insert(57);
  theHeap.insert(13);
  theHeap.insert(12);
  theHeap.insert(9);
  theHeap.insert(10);
  theHeap.dump();

  cout << "--------------------" << endl;
  cout << "*** Then call deleteMin 3 times. ***" << endl; 
  cout << "--------------------" << endl;

  try {
    theHeap.deleteMin();
    theHeap.deleteMin();
    theHeap.deleteMin();
    theHeap.dump();
  }
  catch (MyException &E) { cout << E.getMessage() << endl; }

  cout << "--------------------" << endl;
  cout << "*** Then call deleteMax 3 times. ***"<<endl;
  cout << "--------------------" << endl;

  try {
    theHeap.deleteMax();
    theHeap.deleteMax();
    theHeap.deleteMax();
    theHeap.dump();
  }
  catch (MyException &E) { cout << E.getMessage() << endl; }

  cout << "--------------------" << endl;
  cout << "*** End of given testing ***" << endl << endl;
  
  /* Testing with dPtrHeap using the same file input */
  
  cout << "*** Attempt to get the max and min from dPtrHeap (empty) ***\n";
  cout << "--------------------" << endl;
  
  try { dPtrHeap->getMax(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }

  try { dPtrHeap->getMin(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  cout << endl;
  
  cout << "*** Insert values from input ***" << endl;
  cout << "----------------------" << endl;
  for (unsigned int i = 0; i < dNums.size(); ++i)
    dPtrHeap->insert(dNums[i]);
  
  dPtrHeap->dump();

  cout << "--------------------" << endl;
  cout << "*** Then call deleteMax 2 times. ***"<<endl;
  cout << "--------------------" << endl;
  
  try {
    dPtrHeap->deleteMax();
    dPtrHeap->deleteMax();
    dPtrHeap->dump();
  }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  cout << "--------------------" << endl;
  cout << "*** Then call deleteMin 1 time. ***"<<endl;
  cout << "--------------------" << endl;

  try { dPtrHeap->deleteMin(); }
  catch (MyException &E) { cout << E.getMessage() << endl; }
  
  dPtrHeap->dump();
  
  cout << "--------------------" << endl;
  cout << "End of testing." << endl;
  
  delete fPtrHeap;
  delete dPtrHeap;

  return 0;
}
