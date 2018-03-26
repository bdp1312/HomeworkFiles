#include <iostream>
#include <string>

#include "FileLinkedList.h"

using std::string;
using std::cout;
using std::endl;



int main(){
  FileLinkedList<int> myList("myList");
  //cout<<myList.size()<<endl;
  myList.push_back(555);
  // for(int i = 0; i < 2; ++i){
  //   cout<< "myList["<<i<<"] = "<< myList[i]<<endl;
  // }
 myList.pop_back();

  cout << myList[0]<<endl;
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
