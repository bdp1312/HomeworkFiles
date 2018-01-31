#include<iostream>

#include "ArrayStack.h"

using std::cout;
int main() {
	cout << "stack tester code\n";
	ArrayStack<int>myAStack;
	myAStack.getSpecs();
	if (myAStack.isEmpty()){
		cout<<"empty\n";
	} else {
		cout<<"not empty\n";
	}
	myAStack.push(1);
	cout << myAStack.peek() << "\n";
	if (myAStack.isEmpty()){
		cout<<"empty\n";
	} else {
		cout<<"not empty\n";
	}
	myAStack.push(2);
	cout << myAStack.peek() << "\n";
	cout << myAStack.pop() << "\n";
	cout << myAStack.peek() << "\n";
	for(int i = 0; i < 20; ++i){
		myAStack.push(i);
	}
	cout << myAStack.peek() << "\n";

	myAStack.getSpecs();

	ArrayStack<int>myStackTwo{myAStack};
	for(int i = 0; i < 1000; ++i){
		myStackTwo.push(i);
	}
	cout<<myStackTwo.peek()<<'\n';
	for(int i = 0; i < 1000; ++i){
		myStackTwo.pop();
	}
	ArrayStack<int> myStackThree = myStackTwo;
	myStackThree.push(5);
	cout << myStackThree.pop()<<'\n';

	//ArrayStack<int> myStackTwo = myAStack;

	return 0;
}
