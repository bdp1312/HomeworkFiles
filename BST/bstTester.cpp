#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstdlib>
#include<cstring>
#include<functional>
#include<utility>
#include<map>
#include "BSTMap.h"

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
	// cout<<"size = "<<bst.size()<<endl;
	//
	// bst[5] = "five";
	//
	// cout<<"size = "<<bst.size()<<endl;
	//
	// cout<<"bst[5]= "<<bst[5]<<endl;
	//
	// bst[3] = "three";
	// cout<<"size = "<<bst.size()<<endl;
	// cout<<"bst[3]= "<<bst[3]<<endl;

	bst.insert(make_pair(5, "five"));
	bst.insert(make_pair(2, "two"));
	bst.insert(make_pair(7, "seven"));
	bst.insert(make_pair(1, "one"));
	bst.insert(make_pair(2, "two"));
	bst.insert(make_pair(6, "six"));
	bst.insert(make_pair(9, "nine"));
 	cout<<"eraseing 7\n";
	bst.erase(7);
	cout<<"eraseing 7\n";
	bst.erase(9);

	cout<<"done\n";




	return 0;
}
