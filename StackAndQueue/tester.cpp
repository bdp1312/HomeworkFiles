#include<iostream>

#include "ArrayStack.h"

using std::cout;
int main() {
	cout << "stack and queue tester code\n";
	ArrayStack<int>myAStack;
	myAStack.push(1);
	cout << myAStack.peek() << "\n";
	return 0;
}
