#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<utility>
#include<map>
#include "AVLMap.h"

using std::ofstream;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::rand;
using std::pair;
using std::make_pair;
using std::map;

void printTree(AVLMap<int, string> avl){
  cout<<"printing tree"<<endl;
  for(auto i = avl.begin(); i!=avl.end(); ++i){
    cout<<"key: "<<(*i).first<<" height: "<<i.height()<<endl;
  }
  cout<<"\n\n";
}

int main(){

	AVLMap<int, string> bst;

  bst.insert(make_pair(2, "two"));
  printTree(bst);
  bst.insert(make_pair(3, "three"));
  printTree(bst);
  bst.insert(make_pair(4, "four"));
  printTree(bst);
  bst.insert(make_pair(5, "five"));
  printTree(bst);
  bst.insert(make_pair(6, "six"));
  printTree(bst);
  bst.insert(make_pair(7, "seven"));
  printTree(bst);
  bst.insert(make_pair(8, "eight"));
  printTree(bst);

  return 0;
}
