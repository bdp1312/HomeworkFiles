//test code for hash tabel

#include <iostream>

#include "HashMap.h"

using std::cout;
using std::endline;
using std::vector;

int hasher(int i){return i;}

int main()
{
  HashMap<int, int>(hasher)myMap;

  return 0;
}
