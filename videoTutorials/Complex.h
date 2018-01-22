#ifndef COMPLEX
#define COMPLEX

#include<string>

class Complex{
private:
  double real;
  double imag;	
public:
  Complex(double r, double i);
  Complex(double r);

  double magnitude();
  explicit Complex operator+(Complex c);

  std::string toString();
  
  friend Complex operator *(Complex a, Complex b);	
};

Complex operator *(Complex a, Complex b);

#endif
