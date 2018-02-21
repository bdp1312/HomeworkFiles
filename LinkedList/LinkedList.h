//Benjamin Parrish. Pledged
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<typename T>
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
			i = nullptr;
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
			i=i->prev;
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
			i = sentinal;
			for(int i=0;i<index;++i){
				i = i->next;
			}
		}
		const_iterator(Node *myNode){
			i = myNode;
		}
		const T &operator*(){
			auto retval = i->data;
			return retval;
		}

		bool operator==(const const_iterator &itr){
			return i == iter;
		}
		bool operator!=(const const_iterator &itr){
			return i != iter;
		}
		const_iterator &operator=(const const_iterator &itr) {
			i = iter;
		}
    const_iterator &operator++() {
			i=i->next;
		}
    const_iterator &operator--() {
			i=i->prev;
		}
    const_iterator operator++(int num) {
			for(int i=0; i<num; ++i){
				i=i->next;
			}
    }
    const_iterator operator--(int num) {
			for(int i=0; i<num; ++i){
				i=i->next;
			}
    }
	};
	// General Methods

	LinkedList(){
		sentinal = new Node;
		sentinal->prev = sentinal;
		sentinal->next = sentinal;
	}
	LinkedList &operator=(const LinkedList &al) {
		for(int i = 0; i<top; ++i){

		}
	}
	~LinkedList() {//recursivly remove nodes then free LinkedList
		clear()
		delete [] sentinal;
	void push_back(const T &t){           // add to the end.
		iterator rover = end();
		rover = rover->prev;
		insert(rover, t);
	}
	void pop_back(){                      // remove last element.
		iterator rover = end();
		rover = rover->prev;
		erase(rover);
	}
	int size() const{
		return (top);
	}
	void clear(){
		Node *ptr = end(sentinal);
		for(int i=0; i < top-1;++i){
			Node *temp= ptr;
			ptr = ptr->next;
			erase(temp);
		}
	}
	iterator insert(iterator position,const T &t){    // insert this element before the given index.
		auto pos = position;
		auto newNode = new Node;
		newNode -> data = t;
		newNode ->prev=pos->prev;
		newNode->next=pos->next;
		pos->prev->next= newNode;
		pos->next->prev= newNode;
		top+=1;
		return;
	}
	const T &operator[](int index) const; // get the element at index.
	T &operator[](int index);             // get the element at index.
	iterator erase(iterator pos){    // remove the item at the given index.
		//Node *temp = pos;
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
		delete [] pos;
		top-=1;
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
		Node *ptr = sentinal;
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
#endif
