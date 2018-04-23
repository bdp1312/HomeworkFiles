#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<utility>
#include<map>
#include "Sample.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::rand;
using std::pair;
using std::make_pair;
using std::map;

int main(){
  BSTMap<int, string> bst;

	bst.insert(make_pair(5, "five"));
	bst.insert(make_pair(2, "two"));
	bst.insert(make_pair(7, "seven"));
	bst.insert(make_pair(1, "one"));
	bst.insert(make_pair(2, "two"));
	bst.insert(make_pair(6, "six"));
	bst.insert(make_pair(9, "nine"));

  bst.printTree();

  return 0;

}
