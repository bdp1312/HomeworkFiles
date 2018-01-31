#ifndef ArrayStack_H
#define ArrayStack_H

#include "Stack.h"

template<typename T>
class ArrayStack: public Stack<T>{

private:

  T *myArray;
  int top;//stores number of elements on the stack
  int space;// stores maximum number of elements that can be allocated with currant array.


  public:
    ArrayStack(){
      myArray = new T[10];
      top = -1;
      space = 10;
    }
    ArrayStack(int s){
      myArray = new T[s];
      top = -1;
      space = s;
    }

    ArrayStack(const ArrayStack& a){
      myArray = new T[a.space];
      top = a.top;
      for(int i = 0; i <= top; i++){
        myArray[i] = a.myArray[i];
      }
      space = a.space;
    }

	   ~ArrayStack() //destroys the ArrayStack Object. Deaclocates memory
	    {
	       //remove all elements?
  	  //delete object pointer
      delete [] myArray;
      //myArray = nullptr;
  	  }

    bool isEmpty()const // returns true if there are no values on the stack
    {
      return top == -1;
    }

    void push(const T &t) //adds T to the stack.
  	{
      if(top + 1 == space){
        T *temp = new T[(space * 2) + 1];
        for(int i = 0; i <= space; ++i){
            temp[i] = myArray[i];
        }
        delete [] myArray;
        myArray = temp;
      }
      myArray[top+1] = t;
      top+=1;

  	  // if alocated space is full add more.
  	  // add value to stack
  	  // If value is sucesfuly added, increase size by one.
  	}

  	T pop() //returns the last value on the stack, removes that value
  	{
  	 if(!isEmpty()){
       T returnVal = myArray[top];
       top-= 1;
       return returnVal;
  	  }
    }
  	T peek()const // returns the last value on the stack
  	{
      return myArray[top];
  	  //if isEmpty == True, show stack is empty
  	  //else return value
  	}


};
#endif
