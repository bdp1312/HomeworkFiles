#ifndef LINKEDLIST_H
#define LINKEDLIST_H

templated<typename T>
class ArrayList{
	struct Node{
		T data;
		Node *prev;
		Node *next;

		Node(T *d, Node *p, Node *n){

		}

	};
	Node *sentinal;

public:
	typedef T value_type;
	class iterator{
		Node *i;
	public:
		iterator(){
			Node *i = nullptr;
		}
		iterator(int index){
			i = sentinal;
			for(int i=0;i<index;++i){
				i = i->next;
			}
		}
		iterator(Node *myNode){
			i = myNode;
		}
		T &operator*(){
			return i->data;
		}
		bool operator==(const iterator &itr)const{
			return i == iter;
		}
		bool operator!=(const iterator &itr)const{
			return i != iter;
		}
		iterator &operator=(const iterator &itr){
			i = iter;
		}
		iterator operator++(int num){
			i=i->next;
		}
		iterator operator--(int num){
			i=i->last;
		}
		friend class const_iterator;
		friend class LinkedList;
	};
	class const_iterator{
		Node *i;
	public:


		const T &operaotr*(){

		}
		bool operator*(){

		}
		bool operator==(const const_iterator &itr){

		}
		bool operator!=(const const_iterator &itr){

		}
		const_iterator &operator=(const const_iterator &itr) {

		}
    const_iterator &operator++() {

		}
    const_iterator &operator--() {

		}
    const_iterator operator++(int num) {

    }
    const_iterator operator--(int) {

    }
	};
	// General Methods

	LinkedList(){
		sentinal = new Node;
		sentinal->data = nullptr;
		sentinal->prev = sentinal;
		sentinal->next = sentinal;
	}
	LinkedList &operator=(const LinkedList &al) {
	// TODO
	}
	~LinkedList() {
	 //recursivly remove nodes then free LinkedList
	}
	void push_back(const T &t);           // add to the end.
	void pop_back();                      // remove last element.
	int size() const;
	void clear();
	iterator insert(iterator position,const T &t){    // insert this element before the given index.
		auto pos = position;
		auto newNode = new Node;
		newNode -> data = t;
		newNode ->prev=pos->prev;
		newNode->next=pos->next;
		pos->prev->next= newNode;
		pos->next->prev= newNode;
		return;
	}
	const T &operator[](int index) const; // get the element at index.
	T &operator[](int index);             // get the element at index.
	iterator erase(iterator position){    // remove the item at the given index.

	}
  iterator begin(){
		Node *ptr = sentinal->next;
		return iterator(ptr);
	}
  const_iterator begin() const{
		Node *ptr = sentinal->next;
		return const_iterator(ptr);
	}
	iterator end(){
		Node *ptr = sentinal
		return iterator(ptr);
	}
	const_iterator end() const{
		Node *ptr = sentinal
		return const_iterator(ptr);
	}
	const_iterator cbegin() const{
		Node *ptr = sentinal->next;
		return const_iterator(ptr);
	}
	const_iterator cend() const{
		Node *ptr = sentinal
		return const_iterator(ptr);
	}
	};
