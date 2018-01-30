#ifndef ArrayStack_H
#define ArrayStack_H

#include "Stack.h"

template<typename T>
class ArrayStack: public Stack<T>{

  public:

    ArrayStack(void){
      //allocate array
    }

	   ~ArrayStack() //destroys the ArrayStack Object. Deaclocates memory
	    {
	       //remove all elements?
  	  //delete object pointer
      delete [] ArrayStack;
  	}
  	void push(const T &t) //adds T to the stack.
  	{
  	  // if alocated space is full add more.
  	  // add value to stack
  	  // If value is sucesfuly added, increase size by one.
  	}

  	T pop() //returns the last value on the stack, removes that value
  	{
  	  //if isEmpty == True, show stakc is empty
  	  //else return stack value
  	  //remove stack value
  	}
  	T peek()const // returns the last value on the stack
  	{
  	  //if isEmpty == True, show stack is empty
  	  //else return value
  	}
  	bool isEmpty() // returns true if there are no values on the stack
    {
      if (length == 0){
        return True;
      } else {
        return False;
      }
  	}
    private:
  	Array[T] addSpace //copy class to new array twice as big as
  	}
  private:
    int length = 0;//stores number of elements on the stack
	  int space = 0;// stores maximum number of elements that can be allocated with currant array.
    ArrayStack copy(ArrayStack old)
    {
      //create new array twice the size of old array
      //copy values of old array to new array
    }

};
#endif
