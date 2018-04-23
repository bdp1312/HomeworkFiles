//test code for hash tabel

#include <iostream>
#include<vector>
#include <functional>
#include "HashMap.h"

using std::function;
using std::cout;
using std::endl;
using std::vector;


int hasher(int i){return i;}

int main()
{

  HashMap<int, int, function<int(int)>>myMap(hasher);

  cout<<"test done\n";

  return 0;
}
