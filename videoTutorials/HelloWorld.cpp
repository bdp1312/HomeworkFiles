#include <iostream>
#include <string>
#include "Greet.h"


using namespace std;

int main(int argc, char *argv[]){
//	cout << "hello world!\n";
	string name;
	cout << "What is your name?";
	cin >> name; 
	greet(name);	
	return 0;
}
