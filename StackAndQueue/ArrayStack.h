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
    ArrayStack(int s){//constructor for protected custom size
      if(s > 0){
        myArray = new T[s];
        space = s;
      }
      else{
        myArray = new T[0];
        space = 0;
      }
      top = -1;
    }

    ArrayStack(const ArrayStack& a)//copy constructor
    {
      top = a.top;
      space= a.space;
      myArray=new T[space];
      for(int i = 0; i <= top; i++){
        myArray[i] = a.myArray[i];
      }
    }

    ArrayStack& operator=(const ArrayStack &a) {
      //copy opperator, still needs template arg. is there a way to get around that?
      top = a.top;
      space = a.space;
      T * temp = new T[space];
      for(int i = 0; i <= top; i++){
        temp[i] = a.myArray[i];
      }
      //delete [] myArray;
      myArray = temp;
      return *this;

      //delete [] a.myArray;
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
        for(int i = 0; i < space; ++i){
            temp[i] = myArray[i];
        }
        delete [] myArray;
        myArray = temp;
        space = (space*2)+1;
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
    // void getSpecs(){ //diagnostic method prints top and space vars
    //   std::cout << "top:" << top << "\n";
    //   std::cout << "space" << space << "\n";
    // }


};
#endif
