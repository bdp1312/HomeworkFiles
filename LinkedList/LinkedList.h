//Benjamin Parrish. Pledged
#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
using std::cout;
using std::endl;
template<typename T>
class LinkedList{
	struct Node{
		T data;
		Node *prev;
		Node *next;

		// Node(Node *p, Node* n){
		// 	prev = p;
		// 	next = n;
		// }
		//
		// Node(T d, Node *p, Node *n){
		// 	data = d;
		// 	prev = p;
		// 	next = n;
		// }
	};

	Node sentinal;
	int top;

public:

	typedef T value_type;
	class iterator{
		Node *i;
	public:
		iterator(){
			i = nullptr;
		}
		iterator(int index){
			auto iter = sentinal;
			for(int c=0;c<index;++c){
				iter = iter->next;
			}
		}
		iterator(Node *myNode){
			i = myNode;
		}
		T &operator*(){
			return i->data;
		}
		bool operator==(const iterator &itr)const{
			return i == itr.i;
		}
		bool operator!=(const iterator &itr)const{
			return i != itr.i;
		}
		iterator &operator=(const iterator &itr){
			i = itr.i;
			return *this;
		}
		iterator operator++() {
			i=i->next;
			return *this;
		}
		iterator operator--(){
			i=i->prev;
			return *this;
		}
		iterator operator++(int num){
			return *this;
			i=i->next;
		}
		iterator operator--(int num){
			return *this;
			i = i->prev;
		}
		friend class const_iterator;
		friend class LinkedList;
	};
	class const_iterator{
		Node *i;
	 public:
		const_iterator(){
			i = nullptr;
		}
		const_iterator(int index){
			auto iter = sentinal;
			for(int c=0;c<index;++c){
				iter = iter->next;
			}
		}
		const_iterator(Node *myNode){
			i = myNode;
		}
		const T &operator*(){
			return i->data;
		}

		bool operator==(const const_iterator &itr){
			return i == itr;
		}
		bool operator!=(const const_iterator &itr){
			return i != itr.i;
		}
		const_iterator &operator=(const const_iterator &itr) {
			i = itr.i;
			return *this;
		}
		const_iterator &operator++() {
			i=i->next;
			return *this;
		}
		const_iterator &operator--() {
			i=i->prev;
		}
		const_iterator operator++(int num) {
			for(int c=0; c<num; ++c){
				i=i->next;
			}
		}
		const_iterator operator--(int num) {
			for(int c=0; c<num; ++c){
				i=i->next;
			}
		}
	};


	// General Methods

	LinkedList(){
		sentinal.prev = &sentinal;
		sentinal.next = &sentinal;
		top = 0;
	}
	~LinkedList() { //recursivly remove nodes then free LinkedList
		clear();
		//delete sentinal;
	}
	iterator insert(iterator position,const T &t){    // insert this element before the given index.
		Node *pos = new Node;
		pos -> data = t;
		pos ->prev =position.i->prev;
		pos->next=position.i;
		position.i->prev->next= pos;
		position.i->prev= pos;
		top+=1;
		return pos;
	}
	iterator erase(iterator pos){    // remove the item at the given index.
		auto temp = pos;
		pos.i->prev->next = pos.i->next;
		pos.i->next->prev = pos.i->prev;
		delete [] &pos;
		top-=1;
		return temp;
	}
	void push_back(const T &t){           // add to the end.
		Node *nPtr= new Node;
		nPtr->data = t;
		nPtr->next = &sentinal;
		nPtr->prev = sentinal.prev;
		sentinal.prev->next = nPtr;
		sentinal.prev = nPtr;
	}
	void pop_back(){                      // remove last element.
		iterator rover = end();
		rover.i = rover.i->prev;
		erase(rover);
	}
	int size() const{
		return (top);
	}
	void clear(){
		Node *ptr = &sentinal;
		for(int i=0; i < top-1;++i){
			Node *temp= ptr;
			ptr = ptr->next;
			erase(temp);
		}
	}
	const T &operator[](int index) const{ // get the element at index.
		Node *loc = sentinal;
		for(int i=0; i<index; ++i){
			loc = loc->prev;
		}
		return loc->data;
	}
	T &operator[](int index){
		Node *loc = &sentinal;
		for(int i=0; i<index; ++i){
			//cout<<i<<endl;
			loc = loc->prev;
		}
		return loc->data;
	}           // get the element at index.

  iterator begin(){
		Node *ptr = sentinal.next;
		return iterator(ptr);
	}
  const_iterator begin() const{
		Node *ptr = sentinal.next;
		return const_iterator(ptr);
	}
	iterator end(){
		Node *ptr = &sentinal;
		return iterator(ptr);
	}
	const_iterator end() const{
		Node *ptr = &sentinal;
		return const_iterator(ptr);
	}
	const_iterator cbegin() const{
		Node *ptr = sentinal.next;
		return const_iterator(ptr);
	}
	const_iterator cend() const{
		Node *ptr = sentinal.next->prev;
		return const_iterator(ptr);
	}
	LinkedList &operator=(const LinkedList &al) {
		clear();
		Node*Sptr = &sentinal;
		Sptr->prev=Sptr;
		Sptr->next=Sptr;
		Node OtherNode = al.sentinal;
		OtherNode = *OtherNode.next;
		for(int i = 0; i<al.top; ++i){
			this ->push_back(OtherNode.data);
			OtherNode = *OtherNode.next;
		}
		return *this;
	}
};
#endif
