
#ifndef AVLMAP
#define AVLMAP

#include <utility>
#include <algorithm>
#include <iostream>

template<typename K,typename V>
class AVLMap {
	struct Node {
		Node(Node *p):left(nullptr),right(nullptr),parent(p) {}
		std::pair<K,V> data;
		Node *left;
		Node *right;
		Node *parent;
    int height=1;
	};

	Node *root;
	unsigned int numElems;

public:
	typedef K key_type;
	typedef V mapped_type;
	typedef std::pair<K,V> value_type;

	class const_iterator;

	class iterator {
		Node *n;
		bool end;
	public:
		friend class const_iterator;
		iterator(Node *node):n(node),end(n==nullptr) {}
		iterator(Node *node,bool isEnd):n(node),end(isEnd) {}

		bool operator==(const iterator &i) const { return end==i.end && n==i.n; }
		bool operator!=(const iterator &i) const { return !(*this==i); }
		std::pair<K,V> &operator*() { return n->data; }
		iterator &operator++() {
			if(n==nullptr) return *this;
			if(n->right==nullptr) {
				Node *tmp = n;
				Node *c = n;
				n = n->parent;
				while(n!=nullptr && c==n->right) {
					c = n;
					n = n->parent;
				}
				if(n==nullptr) {
					n = tmp;
					end = true;
				}
			} else {
				n = n->right;
				while(n->left!=nullptr) n = n->left;
			}
			return *this;
		}
		iterator &operator--() {
			if(end) end = !end;
			else {
				if(n->left==nullptr) {
					Node *tmp = n;
					Node *c = n;
					n = n->parent;
					while(n!=nullptr && c==n->left) {
						c = n;
						n = n->parent;
					}
					if(n==nullptr) {
						n = tmp;
						end = true;
					}
				} else {
					n = n->left;
					while(n->right!=nullptr) n = n->right;
				}
			}
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}
		iterator operator--(int) {
			iterator tmp(*this);
			--(*this);
			return tmp;
		}
	};

	class const_iterator {
		Node *n;
		bool end;
	public:
		friend class AVLMap<K,V>;
		const_iterator(Node *node):n(node),end(n==nullptr) {}
		const_iterator(Node *node,bool isEnd):n(node),end(isEnd) {}
		const_iterator(const iterator &iter):n(iter.n),end(iter.end) {}

		bool operator==(const const_iterator &i) const { return end==i.end && n==i.n; }
		bool operator!=(const const_iterator &i) const { return !(*this==i); }
		std::pair<K,V> &operator*() { return n->data; }
		const_iterator &operator++() {
			if(n==nullptr) return *this;
			if(n->right==nullptr) {
				Node *tmp = n;
				Node *c = n;
				n = n->parent;
				while(n!=nullptr && c==n->right) {
					c = n;
					n = n->parent;
				}
				if(n==nullptr) {
					n = tmp;
					end = true;
				}
			} else {
				n = n->right;
				while(n->left!=nullptr) n = n->left;
			}
			return *this;
		}
		const_iterator &operator--() {
			if(end) end = !end;
			else {
				if(n->left==nullptr) {
					Node *tmp = n;
					Node *c = n;
					n = n->parent;
					while(n!=nullptr && c==n->left) {
						c = n;
						n = n->parent;
					}
					if(n==nullptr) {
						n = tmp;
						end = true;
					}
				} else {
					n = n->left;
					while(n->right!=nullptr) n = n->right;
				}
			}
			return *this;
		}
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			++(*this);
			return tmp;
		}
		const_iterator operator--(int) {
			const_iterator tmp(*this);
			--(*this);
			return tmp;
		}
	};

	AVLMap():root(nullptr),numElems(0) {}
	AVLMap(const AVLMap<K,V> &that):numElems(that.numElems) {
		root = recurCopy(that.root,nullptr);
	}
	~AVLMap() {
		deleteAll(root);
	}

	AVLMap &operator=(const AVLMap<K,V> &that) {
		if(&that == this) return *this;
		deleteAll(root);
		root = recurCopy(that.root,nullptr);
		numElems = that.numElems;
		return *this;
	}

	bool empty() const { return numElems == 0; }

	unsigned size() const { return numElems; }

	iterator find(const key_type& k);

	const_iterator find(const key_type& k) const;

	unsigned int count(const key_type& k) const;

	std::pair<iterator,bool> insert(const value_type& val);

	template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
		for(auto iter = first; iter!=last; ++iter) {
			insert(*iter);
		}
	}

	iterator erase(const_iterator position);

	unsigned int erase(const key_type& k);

	void clear();

	mapped_type &operator[](const K &key);

	bool operator==(const AVLMap<K,V>& rhs) const;

	bool operator!=(const AVLMap<K,V>& rhs) const;

  void rotateLeft(Node *node){
		Node *rNode = node->right;
    if(node->parent){
      if(node->parent->data.first>node->data.first){
        node->parent->left=rNode;
      }else{
        node->parent->right=rNode;
      }
			rNode->parent = node->parent;
    } else {
      root = rNode;
      rNode->parent=nullptr;
    }
		node->right=rNode->left;
		node->right->parent=node;
		node->parent=rNode;
		rNode->left = node;
		return;
  }

  void rotateRight(Node *node){
		Node *rNode = node->left;
    if(node->parent){
      if(node->parent->data.first>node->data.first){
        node->parent->left=rNode;
      }else{
        node->parent->right=rNode;
      }
			rNode->parent = node->parent;
    } else {
      root = rNode;
      rNode->parent=nullptr;
    }
		node->left = rNode->right;
		node->left->parent = node;
		node->parent=rNode;
    rNode->right=node;
		return;
  }



  void updateHeight(Node *n, int reqHeight){
		if(n){
			if(n->left && n->right){
				if(n->left->height>n->right->height){
					n->height = (n->left->height)+1;
				} else{
					n->height = (n->right->height)+1;
				}
			} else if(n->left) {
				n->height = (n->left->height)+1;
			} else if(n->right){
				n->height = (n->right->height)+1;
			} else{
				n->height = reqHeight;
			}
//			checkBalance(n);
			updateHeight(n->parent, n->height+1);
		}
	//	std::cout<<"n == nullptr\n";
    return;
  }

	void balanceLeft(Node *n){
		if(n->left->left&&n->left->right){
			if(n->left->left->height>n->left->right->height){
				rotateRight(n);
				n->height = n->height-2;
			} else{
				rotateLeft(n->left);
				rotateRight(n->right);
				n->height = n->height-2;
				--n->left->height;
				++n->left->right->height;
			}
		} else if(n->left->left){
			rotateRight(n);
			n->height = n->height-2;
		} else{
			rotateLeft(n->left);
			rotateRight(n->right);
			n->height = n->height-2;
			--n->left->height;
			++n->left->right->height;
		}
		return;
	}

	void balanceRight(Node *n){
		if(n->right->left&&n->right->right){
			if(n->right->left->height>n->right->right->height){
				rotateRight(n->right);
				rotateLeft(n);
				n->height = n->height-2;
				--n->right->height;
				++n->right->left;
			} else{
				rotateLeft(n);
				n->height = n->height-2;
			}
		} else if(n->right->right){
			rotateLeft(n);
			n->height = n->height-2;
		} else {
			rotateRight(n->right);
			rotateLeft(n);
			n->height = n->height-2;
			--n->right->height;
			++n->right->left;
		}
		return;
	}

  void checkBalance(Node *n){
    if(n->left&&n->right){
      if(n->left->height - n->right->height > 1){
       balanceLeft(n);
      }
      else if(n->left->height - n->right->height < -1){
				balanceRight(n);
      }else{
        return;
      }
    } else if(n->left){
      if(n->left->height>1){
        rotateRight(n);
      }
    } else if(n->right){
      if(n->right->height>1){
        rotateLeft(n);
      }
    } else{
      n->height = 1;
    }
		return;
  }


	iterator begin() {
		Node *n = root;
		while(n->left!=nullptr) n = n->left;
		return iterator(n);
	}

	const_iterator begin() const {
		Node *n = root;
		while(n->left!=nullptr) n = n->left;
		return const_iterator(n);
	}

	iterator end() {
		Node *n = root;
		while(n->right!=nullptr) n = n->right;
		return iterator(n,true);
	}

	const_iterator end() const {
		Node *n = root;
		while(n->right!=nullptr) n = n->right;
		return const_iterator(n,true);
	}

	const_iterator cbegin() const {
		Node *n = root;
		while(n->left!=nullptr) n = n->left;
		return const_iterator(n);
	}

	const_iterator cend() const {
		Node *n = root;
		while(n->right!=nullptr) n = n->right;
		return const_iterator(n,true);
	}

	void printTree() {
		printTreeRecur(root);
		std::cout << std::endl;
	}

private:
	void deleteAll(Node *n) {
		if(n!=nullptr) {
			deleteAll(n->left);
			deleteAll(n->right);
			delete(n);
		}
	}
	Node *recurCopy(Node *n,Node *p) {
		if(n==nullptr) return nullptr;
		Node *n2 = new Node(p);
		n2->data = n->data;
		n2->left = recurCopy(n->left,n2);
		n2->right = recurCopy(n->right,n2);
    n2->height = n->height;
		return n2;
	}
	void printTreeRecur(Node *n) {
		if(n!=nullptr) {
			std::cout << "(";
			printTreeRecur(n->left);
			std::cout << n->data.first << "-" << n->data.second << " ";
			printTreeRecur(n->right);
			std::cout << ")";
		}
	}
	void removeNode(Node *rover) {
		if(rover->left==nullptr && rover->right==nullptr) {
			if(rover==root) root = nullptr;
			else if(rover==rover->parent->left)
				rover->parent->left = nullptr;
			else rover->parent->right = nullptr;
      Node *trimVal=rover->parent;
			delete rover;
      updateHeight(trimVal, 1);
		} else if(rover->left==nullptr) {
			if(rover==root) root = rover->right;
			else if(rover==rover->parent->left) {
				rover->parent->left = rover->right;
				rover->right->parent = rover->parent;
			} else {
				rover->parent->right = rover->right;
				rover->right->parent = rover->parent;
			}
      Node *trimVal=rover->parent;
			delete rover;
      updateHeight(trimVal, 1);
		} else if(rover->right==nullptr) {
			if(rover==root) root = rover->left;
			else if(rover==rover->parent->left) {
				rover->parent->left = rover->left;
				rover->left->parent = rover->parent;
			} else {
				rover->parent->right = rover->left;
				rover->left->parent = rover->parent;
			}
      Node *trimVal=rover->parent;
			delete rover;
      updateHeight(trimVal, 1);
		} else {
			if(rover->left->right==nullptr) {
				Node *tmp = rover->left;
				rover->data = rover->left->data;
				rover->left = rover->left->left;
				if(rover->left!=nullptr) rover->left->parent = rover;
        Node *trimVal=tmp->parent;
				delete tmp;
        updateHeight(trimVal, 1);
			} else {
				Node *n = rover->left->right;
				while(n->right!=nullptr) n=n->right;
				n->parent->right = n->left;
				if(n->left!=nullptr) n->left->parent = n->parent;
				rover->data = n->data;
        Node *trimVal=n->parent;
				delete n;
        updateHeight(trimVal, 1);
			}
		}
	}
};

template <class K, class V>
bool AVLMap<K,V>::operator==(const AVLMap<K,V>& rhs) const {
	if(size()!=rhs.size()) return false;
	for(auto &p:rhs) {
		auto iter = find(p.first);
		if(iter==end() || p.second!=(*iter).second) return false;
	}
	return true;
}

template <class K, class V>
bool AVLMap<K,V>::operator!=(const AVLMap<K,V>& rhs) const {
	return !(*this==rhs);
}

template<typename K,typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::find(const K& key) {
	Node *rover = root;
	while(rover!=nullptr) {
		if(rover->data.first==key) return iterator(rover);
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	return end();
}

template<typename K,typename V>
typename AVLMap<K,V>::const_iterator AVLMap<K,V>::find(const K& key) const {
	Node *rover = root;
	while(rover!=nullptr) {
		if(rover->data.first==key) return const_iterator(rover);
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	return end();
}

template<typename K,typename V>
unsigned int AVLMap<K,V>::count(const key_type& key) const {
	if(find(key)==end()) return 0;
	else return 1;
}

template<typename K,typename V>
std::pair<typename AVLMap<K,V>::iterator, bool> AVLMap<K,V>::insert(const value_type& val) {
	Node *rover = root;
	Node *prev = nullptr;
	while(rover!=nullptr) {
		if(rover->data.first==val.first) return make_pair(iterator(rover),false);
		prev = rover;
		if(val.first<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	++numElems;
	Node *n = new Node(prev);
	n->data = val;
	if(prev==nullptr) {
		root = n;
	} else {
		if(val.first<prev->data.first) prev->left = n;
		else prev->right = n;
	}
	updateHeight(n->parent, 2);
	return make_pair(iterator(n),true);
}

template<typename K,typename V>
typename AVLMap<K,V>::iterator AVLMap<K,V>::erase(const_iterator position) {
	const_iterator tmp = position;
	++tmp;
	removeNode(position.n);
	numElems--;
	return iterator(tmp.n);
}

template<typename K,typename V>
unsigned int AVLMap<K,V>::erase(const K& key) {
	Node *rover = root;
	while(rover!=nullptr) {
		if(rover->data.first==key) {
			removeNode(rover);
			--numElems;
			return 1;
		}
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	return 0;
}

template<typename K,typename V>
void AVLMap<K,V>::clear() {
	numElems = 0;
	deleteAll(root);
	root = nullptr;
}

template<typename K,typename V>
typename AVLMap<K,V>::mapped_type &AVLMap<K,V>::operator[](const K &key) {
	Node *rover = root;
	Node *prev = nullptr;
	while(rover!=nullptr) {
		if(rover->data.first==key) return rover->data.second;
		prev = rover;
		if(key<rover->data.first) rover = rover->left;
		else rover = rover->right;
	}
	++numElems;
	Node *n = new Node(prev);
	n->data.first = key;
	if(prev==nullptr) {
		root = n;
	} else {
		if(key<prev->data.first) prev->left = n;
		else prev->right = n;
	}
	updateHeight(n->parent, 2);
	return n->data.second;
}

#endif
