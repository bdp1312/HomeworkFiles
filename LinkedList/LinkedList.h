#ifndef LINKEDLIST_H
#define LINKEDLIST_H

templated<typename T>
class ArrayList{
	struct Node{
		T *data;
		Node *prev;
		Node *next;
	};

public:
	typedef T value_type;
	class iterator{

	public:
		iterator(){

		}
		T &operaotr*(){

		}
		bool operator==(const iterator &i)const{

		}
		bool operator!=(const iterator &i)const{

		}
		iterator &operator=(const iterator &i){

		}
		iterator operator++(int num){

		}
		iterator operator--(int num){

		}
		friend class const_iterator;
		friend class LinkedList;
	};
	class const_iterator{
		int data;
	public:


		const T &operaotr*(){

		}
		bool operator*(){

		}
		bool operator==(const const_iterator &i){

		}
		bool operator!=(const const_iterator &i){

		}
		const_iterator &operator=(const const_iterator &i) {

		}
    const_iterator &operator++() {

		}
    const_iterator &operator--() {

		}
    const_iterator operator++(int) {

    }
    const_iterator operator--(int) {

    }
	};
