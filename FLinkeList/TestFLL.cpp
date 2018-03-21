#include <iostream>
#include <string>

#include "FileLinkedList.h"

using std::string;
using std::cout;
using std::endl;



int main(){
  FileLinkedList<int> myList("myList");
  myList.push_back(1);
  //pushTest()
  if (myList[0] != 1){
    cout<< "myList[0] == "<<myList[0]<<" should be " << 1 <<endl;
  } else {
    cout<< myList[0]<< endl;
  }

  myList.push_back(15);
  //pushTest()
  if (myList[1] != 15){
    cout<< "myList[1] == "<<myList[1]<<" should be " << 15 <<endl;
  } else {
    cout<< myList[1]<< endl;
  }

  for(int i = 0; i < 2; ++i){
    cout << i<< "-> "<< myList[i]<< endl;
  }
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
