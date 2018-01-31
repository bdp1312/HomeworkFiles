#include<iostream>
#include "ArrayQueue.h"

using std:: cout;
int main() {
	cout << "queue tester code\n";
  ArrayQueue<int>myQueue;
  cout<<myQueue.isEmpty()<<'\n';
  myQueue.enqueue(5);
  cout<<myQueue.peek()<<'\n';
  cout<<myQueue.isEmpty()<<'\n';
  cout<<myQueue.dequeue()<<'\n';
  cout<<myQueue.isEmpty()<<'\n';
  ArrayQueue<char>myOtherQueue;

  return 0;
}
