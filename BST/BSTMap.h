#ifndef BSTMap_H
#define BSTMap_H

#include<iostream>
#include<string>
using std::string;

template<typename K,typename V>


class BSTMap {
    // TODO: Define your Node
    struct Node//node for BST
    {
      Node *parent;
      Node *left;
      Node *right;
      std::pair<K,V> data;
      //int height;

      Node* findMaxChild(){
        Node* n=this; //
        if(n->right != nullptr){n=n->right->findMaxChild();}
        return n;
      }

      Node* findMinChild(){
        Node* n=this;
        if(n->left != nullptr){n=n->left->findMinChild();}
        return n;
      }



      bool operator ==(Node &n){return data.first == n.data.first && data.second==n.data.second;}
      bool operator !=(Node &n){return !(*this==n);}

      bool operator<(Node &n){return data.first < n.data.first;}
      bool operator>(Node &n){return data.first > n.data.first;}

    };

    static Node* findMaxChild(Node *n){
      if(n==nullptr){
        return n;
      }
      if(n->right != nullptr){n=n->right->findMaxChild();}
      return n;
    }

    static Node* findMinChild(Node *n){
      if(n==nullptr){
        return n;
      }
      if(n->left != nullptr){n=n->left->findMinChild();}
      return n;
    }

    void destroy(Node *node){
      if (node){
        destroy(node->right);
        destroy(node->left);
        delete node;
      }
    }

    int numNodes; //number of nodes

    Node* root;//points to base node.

public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K,V> value_type;

    class const_iterator;

    class iterator {

      Node *node;
      Node *root;
        // TODO: Iterator data.
        //Need to be able to go back from end, i.e. --end() should
        //give last element ().
        //One approach is to keep a Node* and a bool that tells me if
        //it is at end.
        //If just keeping Node* and use nullptr to indicate end(), then
        //operator-- need a case for nullptr, in which case to get the
        //maximum element. But to get the maximum element, we need to
        //store information about the tree, e.g. the root pointer, as member.
    public:
        friend class const_iterator;
        iterator(Node* n, Node *r) {
          node = n;
          root = r;
        }
        // TODO: Other constructors as needed.

        bool operator==(const iterator &i) const { return node==i.node && root ==i.root;}
        bool operator!=(const iterator &i) const { return !(*this==i); }
        std::pair<K,V> &operator*() { return node->data; }
        iterator &operator++() {
            if(node->right !=nullptr){
              node = (node->right)->findMinChild();
            } else if(node->parent != nullptr){
              //if((*node)<(*(node->parent))){node = node->parent;}
              while(node->parent!=nullptr&&(*(node->parent))<(*node)){
                node=node->parent;
              }
              node = node->parent;
            } else {
              node = nullptr;
            }
            return *this;
        }
        iterator &operator--() {
          if(node == nullptr){
             node = root->findMaxChild();
           }
          else if(node->left != nullptr){
            node = (node->left)->findMaxChild();
          } else if(node->parent != nullptr){
            while(node->parent != nullptr && *(node->parent) > *node){
              node = node->parent;
            }
            node = node->parent;
          } else { node = nullptr; }
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
        Node *node;
        Node* root;

    public:
        friend class BSTMap<K,V>;  // You might not need this in your code, but it helped me.
        const_iterator(Node* n, Node *r)/*:...*/ {
          root = r;
          node = n;
        }
        // TODO: Other constructors as needed.
        const_iterator(const iterator &iter)/*:...*/ {
          node = iter.node;
          root = iter.root;
        }

        bool operator==(const const_iterator &i) const {return node==i.node && root == i.root; }
        bool operator!=(const const_iterator &i) const {return !(node==i.node); }
        const std::pair<K,V> &operator*() { return node->data; }
        const_iterator &operator++() {
            if(node->right !=nullptr){
              node = (node->right)->findMinChild();
            } else if(node->parent != nullptr){
              //if((*node)<(*(node->parent))){node = node->parent;}
              while(node->parent!=nullptr&&(*(node->parent))<(*node)){
                node=node->parent;
              }
              node = node->parent;
            } else {
              node = nullptr;
            }
            return *this;
        }
        const_iterator &operator--() {
          if(node == nullptr){
             node = root->findMaxChild();
           }
          else if(node->left != nullptr){
            node = (node->left)->findMaxChild();
          } else if(node->parent != nullptr){
            while(node->parent != nullptr && *(node->parent) > *node){
              node = node->parent;
            }
            node = node->parent;
          } else { node = nullptr; }
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



    BSTMap() {
        numNodes = 0;
        root = nullptr;
    }
    ~BSTMap() {
        clear();
    }
    BSTMap(const BSTMap<K,V> &that) {
      numNodes = 0;
      root = nullptr;
      insertTree(that.root);
    }
    void insertTree(Node *nPtr){
      if(nPtr!=nullptr){
        insert (nPtr->data);
        insertTree(nPtr->left);
        insertTree(nPtr->right);
      }
    }

    BSTMap &operator=(const BSTMap<K,V> &that){
      numNodes = 0;
      root = nullptr;
      insertTree(that.root);
    }

    bool empty() const { return size() == 0; }

    unsigned size() const { return numNodes; }

    iterator find(const key_type& k){
      //std::cout<<"finding "<<k<<std::endl;
      Node* n = treeFind(root, k);
      if(n!=nullptr){ return iterator(n, root); }
      else{return end();}
    }

    const_iterator find(const key_type& k) const{
      //std::cout<<"finding "<<k<<std::endl;
      Node *n = treeFind(root, k);
      if(n!=nullptr){ return const_iterator(n, root); }
      else{return cend();}
    }
    Node *treeFind(Node *node, const key_type& k) const{
      if(node == nullptr){return node;}
      else if(node->data.first > k){ return treeFind(node->left, k); }
      else if(node->data.first < k){ return treeFind(node->right, k); }
      else if(node->data.first == k){
        //std::cout<<"key found\n";
        return node;
      }
      else{
      //  std::cout<<"Could not find the key "<<k << std::endl;
        return nullptr;
      }
    }

    unsigned int count(const key_type& k) const {
        if(find(k)!=cend()) return 1;
        else return 0;
    }

    //
    // std::pair<iterator,bool> insert(const value_type& val){
    //
    // }




    std::pair<iterator,bool> insert(const value_type& val){
      //std::cout<<"inserting pair ("<<val.first<<", "<<val.second<<")\n";

      if(size()==0){
        Node *node = new Node{nullptr, nullptr, nullptr, val};
        root = node;
        ++numNodes;
        return std::make_pair(iterator(node, root), true);
      }
      iterator one = find(val.first);
      if(one == end()){
        auto first=addNode(val, root);
        //std::cout<<"inserted ("<<val.first<<", "<<val.second<<")\n";
        auto second=true;
        //std::cout<<"node added.\n";
        ++numNodes;
        return std::make_pair(first, second);
      } else{
        auto first = one;
        auto second = false;
        return std::make_pair(first, second);
      }
    }



    iterator addNode(const value_type& val, Node *pater){
      if((pater->data).first< val.first){
        if(pater->right == nullptr){
          Node* node = new Node{pater, nullptr, nullptr, val};
          pater->right = node;
          return iterator(node, root);
        }else{return addNode(val, pater->right);}
      } else if((pater->data).first>val.first){
        if(pater->left == nullptr){
          Node* node = new Node{pater, nullptr, nullptr, val};
          pater->left = node;
          return iterator(node, root);
        } else {
          return addNode(val, pater->left);
        }
      } else if((pater->data).first==val.first){
        //std::cout<<"error: two nodes found with the key of "<<val.first<<std::endl;
        pater->data = val;
        return iterator(pater, root);
      } else{
        return end();
      }
    }

    int height(Node *node){
      if(node == nullptr) {return 0;}
      return node->height;
    }

    // void updateH(Node *node){
    //   if(node==nullptr){return;}
    //   node->height = ;
    //   updateH(node-> parent)
    // }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(auto iter = first; iter!=last; ++iter) {
            insert(*iter);
        }
    }




    iterator erase(const_iterator position){
      if(position.node->left ==nullptr&&position.node->right==nullptr){
        if(position.node->parent != nullptr){
          if(*(position.node->parent)<*(position.node)){position.node->parent->right=nullptr;}
          else{position.node->parent->left=nullptr;}
        }
        iterator retval=iterator((++position).node, root);
        delete position.node;
        --numNodes;
        return retval;
      }
      else if(++position==cend()){
        if(position.node->parent==nullptr){
          root = position.node->left;
          position.node->left->parent = nullptr;
          delete position.node;
        } else {
          position.node->parent->right=position.node->left;
          position.node->left->parent= position.node->left;
          delete position.node;
        }
        --numNodes;
        return end();
      } else {
        position.node = (++position.node);
        replace(++position);
        return iterator(++position.node, root);
      }
    }

    void replace(const_iterator position){
      if(position.node->right==nullptr&&position.node->left==nullptr){
        if(position.node->parent != nullptr){
          if(*(position.node->parent)<*(position.node)){position.node->parent->right=nullptr;}
          else{position.node->parent->left=nullptr;}
        }
        delete position.node;
        --numNodes;
        return;
      }
      else if(++position==cend()){
        if(position.node->parent==nullptr){
          root = position.node->left;
          position.node->left->parent = nullptr;
          delete position.node;
        } else {
          position.node->parent->right=position.node->left;
          position.node->left->parent= position.node->left;
          delete position.node;
        }
        --numNodes;
        return;
      } else {
        replace(++position);
        return;
      }
    }

    //   auto retval= iterator(position.node, root);
    //   ++retval;
    //   if(position.node->right!=nullptr){
    //     Node *replacement = position.node->right->findMinChild();
    //     fixParent(replacement);
    //     replacement->right = position.node->right;
    //     replacement->left = position.node->left;
    //     replacement->parent = position.node->parent;
    //     if(position.node->parent ==nullptr){
    //       root = replacement;
    //     } else if(*(position.node->parent)>*(position.node)){
    //       position.node->parent->left = replacement;
    //     } else{
    //       position.node->parent->right = replacement;
    //     }
    //     delete (position.node);
    //     --numNodes;
    //     position.node= replacement;
    //     //  return end();
    //   } else if(position.node->left!=nullptr){
    //     Node *replacement = findMaxChild(position.node->left);
    //     fixParent(replacement);
    //     replacement->right = position.node->right;
    //     replacement->left = position.node->left;
    //     replacement->parent = position.node->parent;
    //
    //     if(position.node->parent ==nullptr){
    //       root = replacement;
    //     } else if(*(position.node->parent)>*(position.node)){
    //       position.node->parent->left = replacement;
    //     } else{
    //       position.node->parent->right = replacement;
    //     }
    //
    //     delete (position.node);
    //     --numNodes;
    //     position.node= replacement;
    //     //return end();
    //   } else{
    //     fixParent(position.node);
    //     delete (position.node);
    //     --numNodes;
    //     //return end();
    //   }
    //   return retval;
    // }
    // void fixParent(Node *replacement){
    //
    //   if(replacement->parent == nullptr){
    //     root = nullptr;
    //   }else if((replacement->parent->data).first>(replacement->data).first){
    //     if(replacement->right){
    //       replacement->parent->left = replacement->right;
    //       if(replacement->right){
    //         replacement->right->parent = replacement->parent;
    //       }
    //     } else{
    //       replacement->parent->left = replacement->left;
    //       if(replacement->left){
    //         replacement->left->parent = replacement->parent;
    //       }
    //     }
    //
    //   } else if((replacement->parent->data).first<(replacement->data).first){
    //     if(replacement->left){
    //       replacement->parent->right = replacement->left;
    //       if(replacement->left){
    //         replacement->left->parent = replacement->parent;
    //       }
    //     } else{
    //       replacement->parent->right = replacement->right;
    //       if(replacement->right){
    //         replacement->right->parent = replacement->parent;
    //       }
    //     }
    //
    //
    //   } else{
    //     //std::cout<<"error: identical key found. 1\n";
    //   }
    // }

    unsigned int erase(const key_type& k){
        const_iterator it = find(k);
        if (it!=cend()) {
            erase(it);
            return 1;
        }
        else {
            return 0;
        }
    }

    void clear(){
      eraseTree(root);
      numNodes = 0;
    }

    void eraseTree(Node *node){
      if(node!=nullptr){
        eraseTree(node->left);
        eraseTree(node->right);
        delete node;
      }
    }

    mapped_type &operator[](const K &key){
        return (*insert(make_pair(key, V())).first).second;
    }


    bool operator==(const BSTMap<K,V>& rhs) const{
      auto valOne = begin();
      auto valTwo = rhs.begin();
      while(valOne!= end() && valTwo != rhs.end()){
        if(*valOne != *valTwo){return false;}
        ++valOne;
        ++valTwo;
      }
      if(valOne == end() && valTwo == rhs.end()){return true;}
      else{return false;}
    }

    bool operator!=(const BSTMap<K,V>& rhs) const { return ! (*this == rhs); }

    iterator begin() { return iterator(findMinChild(root), root); }//returns smallest element

    const_iterator begin() const { return const_iterator(findMinChild(root), root); }

    iterator end() { return iterator(nullptr, root); }//returns largest element

    const_iterator end() const { return const_iterator(nullptr, root); }

    const_iterator cbegin() const { return const_iterator(findMinChild(root), root); }

    const_iterator cend() const { return const_iterator(nullptr, root); }

};

#endif
