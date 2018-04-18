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


	for(auto i = bst.cbegin(); i != bst.cend(); ++i){
		cout<<(*i).first<<"\n";
		cout<<endl;
	}

	bst.trace();

	// auto o = bst.cbegin();
	// auto a = constant(o);

	// cout<<(*o).first<<"\n";
	// cout<<(*a).first<<"\n";
	cout<<"eraseing 5\n";
	bst.erase(5);
	bst.trace();
	cout<<"eraseing 7\n";
	bst.erase(7);
	bst.trace();
	cout<<"eraseing 9\n";
	bst.erase(9);
	bst.trace();
	bst.clear();
	cout<<"done\n";




	return 0;
}
