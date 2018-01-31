#include"Queue.h"

#ifndef ArrayQueue_H
#define ArrayQueue_H

template<typename T>
class ArrayQueue: public Queue<T>{
  private:
    int start; //last element dequeued
    int size; //first element dequeued
    int space;//size of the array
    T *myArray;// array pointer

  public:
    ArrayQueue()//default constructor
    {
      start = 0;
      size = 0;
      space = 10;
      myArray = new T[space];
    }
    ArrayQueue(int s)//varrible size constructor
    {
      start = 0;
      size = 0;
      if (s>0){
        space = s;
      } else {
        space = 0;
      }
      myArray = new T[space];
    }

    ArrayQueue(const ArrayQueue &a)//copy constructor
    {
      start = a.start;
      size = a.size;
      space= a.space;
      myArray=new T[space];
      for(int i = 0; i < space; ++i){
        myArray[i] = a.myArray[i];
      }
    }

    ArrayQueue& operator=(const ArrayQueue &a) {
      //copy opperator, still needs template arg. is there a way to get around that?
      start = a.start;
      size = a.size;
      space = a.space;
      T * temp = new T[space];
      for(int i = 0; i < space; i++){
        temp[i] = a.myArray[i];
      }
      myArray = temp;
      return *this;
    }


    ~ArrayQueue() {delete [] myArray;}//destuctor

    bool isEmpty()const{ //returns true if start == start == 0
      return size == 0;
    }

    void enqueue(const T &t){
      if (size == space){
        T * temp = new T[(space*2)+1];
        for(int i = start; i < space; ++i){
          temp[i - start] = myArray[i];
        }
        for(int i = 0; i < start; ++i){
          temp[space-start+i] = myArray[i];
        }
        delete [] myArray;
        myArray = temp;
        space = (space*2)+1;
      }
      myArray[(start + size) % space] = t;
      ++size;
    }

    T dequeue(){
      if(!isEmpty()){
        int retIndex = start;
        ++start;
        if(start == space){start = 0;}
        --size;
        return myArray[retIndex];
      }
    }

    T peek() const{
      if(!isEmpty()){
        return myArray[start];
      }
    }
};
#endif
