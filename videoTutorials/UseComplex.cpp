#include<iostream>
#include<string>

#include "Complex.h"

int main (int arg,char *argv[]){
  Complex a(1,2);
  Complex b(3,4); 
  Complex c(a+b);
  Complex d(4*a);
  Complex e(4+a);  
  return 0;
}
