//test code for ArrayList
#include<iostream>
#include<string>

#include "ArrayList.h"

using std::cout;
using std::string;
using std::to_string;


void empty(ArrayList<int> l, int i){
	if(!l.isEmpty()){
	cout<<"FAIL: List is not empty."<< i <<"\n";
	}
}
void empty(ArrayList<string> l, int i){
	if(!l.isEmpty()){
	cout<<"FAIL: List is not empty."<< i <<"\n";
	}
}

void equals(ArrayList<int> l, int val, int i){
	if(l.look(l.size()) != val){
		cout<<"FAIL: Values don't match"<< l.look(l.size()) << val << i <<"\n";
	}
}
void equals(ArrayList<string> l, string val, int i){
	if(l.look(l.size()) != val){
		cout<<"FAIL: Values don't match"<< l.look(l.size()) << val << i <<"\n";
	}
}


int main(){
	ArrayList<int> myList;
	ArrayList<string> myListTwo;
	empty(myList, 1);
	empty(myListTwo, 2);

	for(int i=0; i<10; ++i){
		myList.push_back(i);
		equals(myList, i, (3+i));
	}

	for(int i=0; i<10; ++i){
		string a = to_string(i) + to_string(i+1) + to_string(i+2);
		myListTwo.push_back(a);
		equals(myListTwo, a, 11+i);
	}

	cout<<"test Compleate\n";
	return 1;
}
