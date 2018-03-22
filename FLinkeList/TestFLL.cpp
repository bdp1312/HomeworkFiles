#include <iostream>
#include <string>

#include "FileLinkedList.h"

using std::string;
using std::cout;
using std::endl;



int main(){
  FileLinkedList<int> myList("myList");
  myList.push_back(1);
  cout<< myList[0]<<endl;
  
  cout<<"test done"<<endl;
  return 0;
}
// void compare(int index, int val){
//   int ret = myList[index];
//   if (myList[index] != val){
//     cout<< "myList["<< index << "] == "<<ret<<" should be " << val <<endl;
//   }
// }
// void pushTest(){
//   myList.push_back(1);
//   compare(0, 1);
//
// }
