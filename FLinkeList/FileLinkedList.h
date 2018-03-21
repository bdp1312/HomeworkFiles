#ifndef FileArrayList_h
#define FileArrayList_h

#import <iostream>

using std::cout;
using std::endl;


template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // TODO - Your private data.

        FILE *f;
        int filesize; //space at which the file ends
        int freespace; //pointer to unalocated node, ==-1 if none exist
        int nodeSize = sizeof(T)+sizeof(int)*2;//size of node

        // struct Node{
        //   T data;
        //   int prev;
        //   int next;
        // }
        //could use for read and write node
        // TODO - Private helper functions. (Maybe file IO with an index.)


        //determines location of previous node, node is location in file
        static int readPrev(int node, FILE *f){
          int temp;
          if(node ==0){
            fseek(f, sizeof(int), SEEK_SET);
          }else {
            fseek(f, node + sizeof(T), SEEK_SET);
          }
          fread(&temp, sizeof(int),1,f);
          return temp;
        }
        //determines location of the next node
        static int readNext(int node, FILE *f){
          int temp;
          if(node==0){
            fseek(f, sizeof(int)*2, SEEK_SET);
          } else {
            fseek(f, node+sizeof(T)+sizeof(int), SEEK_SET);
          }
          fread(&temp, sizeof(int), 1, f);
          return temp;
        }
        void writePrev(int node, int pos, FILE *f){
          if(node==0){
            fseek(f, sizeof(int), SEEK_SET);
          }else{
            fseek(f, node + sizeof(T), SEEK_SET);
          }
          fwrite(&pos, sizeof(int), 1, f);
        }
        void writeNext(int node, int pos, FILE *f){
          if(node==0){
            fseek(f, sizeof(int)*2, SEEK_SET);
          }else{
            fseek(f, node+sizeof(T)+sizeof(int), SEEK_SET);
          }
          fwrite(&pos, sizeof(int), 1, f);
        }
        static T readData(int node, FILE* f){
          T retval;
          fseek(f, node, SEEK_SET);
          fread(&retval, sizeof(T), 1, f);
          cout<< "reading at " << node<<endl;
          return retval;
        }
        void writeData(int node, T t, FILE* f){
          fseek(f, node, SEEK_SET);
          fwrite(&t, sizeof(T), 1, f);
        }

        static int readSize(FILE *f){
          int temp;
          fseek(f, 0, SEEK_SET);
          fread(&temp, sizeof(int), 1, f);
          return temp;
        }
        void writeSize(int temp, FILE *f){
          fseek(f, 0, SEEK_SET);
          fwrite(&temp, sizeof(int), 1, f);
        }

    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                FILE *file;
                int pos; //holds location of node in file
              public:
                const_iterator(int i, FILE *f){//position in file, file object
                  cout<< "i = "<< i << endl;
                  pos = i;
                  cout<<pos<<endl;
                  file = f;
                }
                const_iterator(const const_iterator &i){
                  pos = i.pos;
                  file = i.file;
                }
                T operator*(){
                  T temp = readData(pos, file);
                  return temp;
                }
                bool operator==(const const_iterator &i) const{
                  return(pos==i.pos && file==i.file);
                }
                bool operator!=(const const_iterator &i) const{
                  return(pos!=i.pos||file!=i.file);
                }
                const_iterator &operator=(const const_iterator &i){
                  pos=i.pos;
                  file=i.file;
                  return *this;
                }
                const_iterator &operator++(){
                  pos = readNext(pos, file);
                  return *this;
                }
                const_iterator &operator--(){
                  pos=readPrev(pos, file);
                  return *this;
                }
                const_iterator operator++(int){
                  const_iterator oldPos(pos, file);
                  pos = readNext(pos, file);
                  return oldPos;
                }
                const_iterator operator--(int){
                  const_iterator oldPos(pos, file);
                  pos=readPrev(pos, f);
                  return oldPos;
                }

                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname){
          f=fopen(fname.c_str(), "r+b");
          if(f!=nullptr){
            readSize(f);
            fseek(f, 0, SEEK_SET);
            fread(&freespace, sizeof(int), 1, f);
          } else {
            f = fopen(fname.c_str(), "w+b");
            readPrev(0, f);
            readNext(0, f);
            filesize = sizeof(int)*4;
            writeSize(filesize, f);

            cout<< "filesize = "<< filesize<<endl;
            freespace=-1;
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.

        }
        ~FileLinkedList(){
          writeSize(filesize, f);
          fseek(f, sizeof(int)*3, SEEK_SET);
          fwrite(&freespace, sizeof(int), 1, f);
          fclose(f);
        }

        void push_back(const T &t) { insert(end(),t); }
        void pop_back() { erase(--end()); }
        int size() const{return filesize;}
        void clear() { while (size()>0) pop_back(); }

        const_iterator insert(const_iterator position, const T &t){
          //filesize = readSize(f);
          //cout<<"filesize: "<< filesize<<endl;
          const_iterator myNode(readSize(f), f);
          if (freespace != -1){
            myNode.pos = freespace;
            //fseek(f, freespace, SEEK_SET);
            freespace = readNext(freespace, f);
          } else {
            filesize= filesize + nodeSize;

          }
          cout<<"myNode.pos "<<myNode.pos<<endl;
          //fwrite(&t, sizeof(T); 1, f);
          writeData(myNode.pos, t, f);
         cout<< "inserting at: " << position.pos << endl;
                    //fseek(f, sizeof(int), SEEK_CUR);
          //fwrite(&readPrev(position.pos, f), sizeof(int), 1, f);
          writeNext(myNode.pos, position.pos, f);
          //fseek(f, sizeof(int), SEEK_CUR);
          //fwrite(&readNext(position.pos, f), sizeof(int), 1, f);
          writePrev(myNode.pos, readPrev(position.pos, f), f);
          cout<< "seting myNode -> prev to: " <<readPrev(position.pos, f)<<endl;
          writeNext(readPrev(myNode.pos, f), myNode.pos, f);
          cout<< "setting myNode.prev -> next to "<< myNode.pos << endl;
          writePrev(position.pos, myNode.pos, f);
          return myNode;
        }
        T operator[](int index) const{
            auto itr=begin();
            for (int i=0;i<index;++i){
              itr++;
            }
            return *itr;
        }
        const_iterator erase(const_iterator position){
          if(position == end()){
            filesize = filesize - nodeSize;
          } else {
            writeNext(readPrev(position.pos, f), readNext(position.pos, f), f);
            writePrev(readNext(position.pos, f), readPrev(position.pos, f), f);
            writeNext(position.pos, freespace, f);
            freespace = position.pos;
          }
          return --position;
        }
        void set(const T &value,int index){
          auto iter = begin();
          for(int i = 0; i<index;++i){
            iter.pos = readNext(iter.pos, f);
          }
          fseek(f, iter.pos, SEEK_SET);
          fwrite(&value, sizeof(T), 1, f);
        }
        void set(const T &value,const_iterator position){
          fseek(f, position.pos, SEEK_SET);
          fwrite(&value, sizeof(T), 1, f);
        }

        const_iterator begin(){
          return const_iterator(readNext(0, f), f);
        }
        const_iterator begin() const{
          return const_iterator(readNext(0, f), f);
        }
        const_iterator end(){
          return const_iterator(0, f);
        }
        const_iterator end() const{
          return const_iterator(0, f);
        }
        const_iterator cbegin() const{
          return const_iterator(readNext(0, f), f);
        }
        const_iterator cend() const{
          return const_iterator(0, f);
        }
};
#endif
