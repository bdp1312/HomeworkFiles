#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<string>

using std::string;

template<typename T>
class LinkedList {
                struct Node {
                        // TODO
                };
                // TODO - Your data
        public:
                typedef T value_type;

                class iterator {
                                // TODO - Data
                        public:
                                // TODO - Constructors
                                T &operator*() {  TODO }
                                bool operator==(const iterator &i) const { TODO }
                                bool operator!=(const iterator &i) const { TODO }
                                iterator &operator=(const iterator &i) { TODO }
                                iterator &operator++() { TODO }
                                iterator &operator--() { TODO }
                                iterator operator++(int) {
                                        // TODO
                                }
                                iterator operator--(int) {
                                        // TODO
                                }
                                friend class const_iterator;
                                friend class LinkedList;
                };
                class const_iterator {
                                // TODO - Data
                        public:
                                // TODO - Constructors
                                // TODO - Include a constructor that converts from a regular iterator.
                                const T &operator*() { TODO }
                                bool operator==(const const_iterator &i) const { TODO }
                                bool operator!=(const const_iterator &i) const { TODO }
                                const_iterator &operator=(const const_iterator &i) { TODO }
                                const_iterator &operator++() { TODO }
                                const_iterator &operator--() { TODO }
                                const_iterator operator++(int) {
                                        // TODO
                                }
                                const_iterator operator--(int) {
                                        // TODO
                                }
                };

                // General Methods

                // TODO - Constructors

                LinkedList &operator=(const LinkedList &al) {
                    // TODO
                }
                ~LinkedList() {
                        // TODO
                }
                void push_back(const T &t);           // add to the end.
                void pop_back();                      // remove last element.
                int size() const;
                void clear();
                iterator insert(iterator position,const T &t);    // insert this element before the given index.
                const T &operator[](int index) const; // get the element at index.
                T &operator[](int index);             // get the element at index.
                iterator erase(iterator position);               // remove the item at the given index.

                iterator begin();
                const_iterator begin() const;
                iterator end();
                const_iterator end() const;
                const_iterator cbegin() const;
                const_iterator cend() const;
};

#endif
