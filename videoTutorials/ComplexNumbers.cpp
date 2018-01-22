#include<cmath>

#include "Complex.h"
using namespace std;

Complex::Complex(double r,double i):real(r),imag(i){}

Complex::Complex(double r):real(r),imag(0.0) {}

double Complex::magnitude() {
  sqrt(real*real+imag+imag);
}

Complex Complex::operator+(Complex c) {
  return Complex(real+c.real, imag+c.imag);
}
  string Complex::toSTring() {
  string ret;
  ret += real;
  ret += "+";
  ret += imag;
  ret +=  "+";
  return ret;
}

Complex operator *(Complex a, Complex b){
  return Complex(a.real*b.real-a.imag*b.imag, a.real*b.real+a.imag*b.real);
} 
