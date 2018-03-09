#include <string>
#include <iostream>
#include "FileArrayList.h"
using std::cout;
using std::endl;

void pushTest(int n, FileArrayList<int> list){
  list.push_back(n);
  auto i = list[0];
  cout<< n << " got back " << i;
}

int main(){
  FileArrayList<int> mylist("myList.bin");
  pushTest(5, mylist);
  return 0;
}
