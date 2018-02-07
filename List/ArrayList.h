//Benjamin Parrish, Pledged.
#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<typename T>
class ArrayList{

private:
  T *data;
  //T **dataPtr;
  int space;
  int top;

public:
ArrayList(){
  space = 10;
  top = -1;
  data = new T[space];
  //dataPtr = new *T[space]
}

ArrayList(const ArrayList &a){
  space = a.space;
  top=a.top;
  data=new T[space]
  for(int i=0; i<space; ++i){
    data[i] = a.data[i];
  }
}

ArrayList<T> &operator=(const ArrayList<T> &a){
  space = a.space;
  top = a.size;
  space = a.space;
  T * temp = new T[space];
  for(int i = 0; i < space; i++){
    temp[i] = a.data[i];
  }
  myArray = temp;
  return *this;
}

void grow(){
  temp = new T[(space*2)+1]
  for(int i=0;i<space;++i){
    temp[i] = data[i];
  }
  delete [] data;
  data = temp;
}

~ArrayList(){
  delete [] data;
  //delete [] dataPtr;
}

void push_back(const T &t){           // add to the end.
  if((top+1) == space){
    grow();
  }
  top+=1;
  data[top] = t;
}
void pop_back(){                      // remove last element.
  T retval = data[top];
  --top;
  return retval;
}
int size() const{
  return top;
}
void clear(){
  top=-1;
}
void insert(const T &t,int index){   // insert this element before the given index.
  if((top+1) == space){
    grow();
  }
  for(int i = index; i < space){
    data[i+1]=data[i];
  }
  ++top;
  data[index] = t;
}
const T &operator[](int index) const{ // get the element at index.

}
T &operator[](int index);             // get the element at index.
void remove(int index);               // remove the item at the given index.

class iterator{
  iterator(T *l);
  iterator();
  iterator(const iterator &i);
  T &operator*();
  bool operator==(const iterator &i) const;
  bool operator!=(const iterator &i) const;
  iterator &operator=(const iterator &i);
  iterator &operator++();
  iterator &operator--();
  iterator operator++(int);
  iterator operator--(int);
};

iterator begin();
const iterator begin() const;
iterator end();
const iterator end() const;
const iterator cbegin() const;
const iterator cend() const;


};



#endif
