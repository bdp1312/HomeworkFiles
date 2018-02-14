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
  data=new T[space];
  for(int i=0; i<space; ++i){
    data[i] = a.data[i];
  }
}

ArrayList<T> &operator=(const ArrayList<T> &a){
  space = a.space;
  top = a.top;
  space = a.space;
  T * temp = new T[space];
  for(int i = 0; i < space; i++){
    temp[i] = a.data[i];
  }
  data = temp;
  return *this;
}

bool isEmpty(){
  return top == -1;
}

void grow(){
  T *temp = new T[(space*2)+1];
  for(int i=0;i<space;++i){
    temp[i] = data[i];
  }
  delete [] data;
  data = temp;
  space = (space*2)+1;
}

~ArrayList(){
  delete [] data;
  //delete [] dataPtr;
}

T look(int i) {
  return data[i];
}

void push_back(const T &t){           // add to the end.
  if((top+1) == space){
    grow();
  }
  ++top;
  data[top] = t;
}
void pop_back(){                      // remove last element.
  //T retval = data[top];
  --top;
}
int size() const{
  return top+1;
}
void clear(){
  top=-1;
  delete [] data;
  data = new T[10];
  space = 10;
}
void insert(const T &t,int index){   // insert this element before the given index.
  if((top+1) == space){
    grow();
  }
  for(int i = top; i >= index; --i){
    data[i+1]=data[i];
  }
  ++top;
  data[index] = t;
}
const T &operator[](int index) const{ // get the element at index.
  return *data[index];
}
T &operator[](int index){
  return data[index];
}             // get the element at index.
void remove(int index){               // remove the item at the given index.
  for(int i = index; i < top; ++i){
    data[i] = data[i+1];
  }
  --top;
}
class iterator{
  T *i;
public:
  iterator(T *l){
    i = l;
  }
  iterator(){
    i = nullptr;
  }
  iterator(const iterator &otherI){
    i = otherI.i;
  }
  T &operator*(){
    return *i;
  }
  bool operator==(const iterator &otherI) const{
    return i==otherI.i;
  }
  bool operator != (const iterator &otherI) const{
    return i!=otherI.i;
  }
  iterator &operator=(const iterator &otherI){
    i = otherI.i;
  }
  iterator &operator++(){
    ++i;
    return *this;
  }
  iterator &operator--(){
    --i;
    return *this;
  }
  iterator operator++(int){
    T *temp = i;
    i++;
    return iterator(temp);
  }
  iterator operator--(int){
    auto temp = i;
    i--;
    return iterator(temp);
  }
};

class const_iterator{
  T *i;
public:
  const_iterator(T *l){
    i = l;
  }
  const_iterator(){
    i = nullptr;
  }
  const_iterator(const const_iterator &otherI){
    i = otherI.i;
  }
  T &operator*(){
    return *i;
  }
  bool operator==(const const_iterator &otherI) const{
    return i==otherI.i;
  }
  bool operator != (const const_iterator &otherI) const{
    return i!=otherI.i;
  }
  const_iterator &operator=(const const_iterator &otherI){
    i = otherI.i;
  }
  const_iterator &operator++(){
    ++i;
    return *this;
  }
  const_iterator &operator--(){
    --i;
    return *this;
  }
  const_iterator operator++(int){
    T *temp = i;
    i++;
    return const_iterator(temp);
  }
  const_iterator operator--(int){
    auto temp = i;
    i--;
    return const_iterator(temp);
  }
};

iterator begin(){
  int *ptr=&data[0];
  return iterator(ptr);
}
const_iterator begin() const{
  int *ptr=&data[0];
  return const_iterator(ptr);
}
iterator end(){
//  int retval = top+1;
  int *ptr = &data[top+1];
  return iterator(ptr);
}

const_iterator end() const{
  int *ptr = &data[top];
  return const_iterator(ptr);
}
const_iterator cbegin() const{
  int *ptr=&data[0];
  return const_iterator(ptr);
}
const_iterator cend() const{
  int *ptr = &data[top];
  return const_iterator(ptr);
}
};



#endif
