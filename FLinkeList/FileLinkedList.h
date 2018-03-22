#ifndef FileArrayList_h
#define FileArrayList_h

#include <iostream>

using std::cout;
using std::endl;


template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // TODO - Your private data.

        FILE *f;
        int filesize; //space at which the file ends

        //int size; //number of alocated nodes

        int freespace; //pointer to unalocated node, ==-1 if none exist
        static const int nodeSize = sizeof(T)+2*sizeof(int);//size of node

        // struct Node{
        //   T data;
        //   int prev;
        //   int next;
        // }
        //could use for read and write node
        // TODO - Private helper functions. (Maybe file IO with an index.)


        //determines location of previous node, node is location in file
        static int readPrev(int node, FILE *f){
          cout<<"readPrev "<<"node: "<< node<<endl;
          int temp;
          fseek(f, node*nodeSize + sizeof(T)+2*sizeof(int), SEEK_SET);
          fread(&temp, sizeof(int),1,f);
          return temp;
        }
        //determines location of the next node
        static int readNext(int node, FILE *f){
          cout<<"readnext "<<"node: "<< node<<endl;
          int temp;
          fseek(f, node*nodeSize+sizeof(T)+3*sizeof(int), SEEK_SET);
          fread(&temp, sizeof(int), 1, f);
          return temp;
        }
        void writePrev(int node, int pos, FILE *f){
          cout<<"writePrev "<<"node: "<< node<<" pos: "<<pos<<endl;
          fseek(f, node*nodeSize + sizeof(T)+2*sizeof(int), SEEK_SET);
          fwrite(&pos, sizeof(int), 1, f);
        }
        void writeNext(int node, int pos, FILE *f){
          cout<<"writeNext "<<"node: "<< node<<" pos: "<<pos<<endl;
          fseek(f, node*nodeSize+sizeof(T)+3*sizeof(int), SEEK_SET);
          fwrite(&pos, sizeof(int), 1, f);
        }
        static T readData(int node, FILE* f){
          cout<<"readData "<<"node: "<< node<<endl;
          if(node == 0){
            cout<< "warning! reading from the sentinal\n";
          }
          T retval;
          fseek(f, node*nodeSize+2*sizeof(int), SEEK_SET);
          fread(&retval, sizeof(T), 1, f);
          return retval;
        }
        void writeData(int node, T t, FILE* f){
          cout<<"writeData "<<"node: "<< node<<endl;
          if(node == 0){
            cout<< "warning! writing to the sentinal\n";
          }
          fseek(f, node, SEEK_SET);
          fwrite(&t, sizeof(T), 1, f);
          cout<< "writing to "<< node<< endl;
        }

        static int readSize(FILE *f){
          int temp;
          fseek(f, 0, SEEK_SET);
          fread(&temp, sizeof(int), 1, f);
          cout<<"filesize=" << temp<<endl;
          return temp;
        }
        void writeSize(int temp, FILE *f){
          filesize= temp;
          cout<<"writeSize "<<"temp: "<< temp<<endl;
          fseek(f, 0, SEEK_SET);
          fwrite(&temp, sizeof(int), 1, f);
        }
        static int readFreespace(FILE* f){
          int temp;
          fseek(f, sizeof(int), SEEK_SET);
          fread(&temp, sizeof(int), 1, f);
          cout<<"freespace = "<< temp<<endl;
          return temp;
        }
        void writeFreespace(int n, FILE *f){
          cout<<"writeFreespace "<<"n: "<< n<<endl;
          fseek(f, sizeof(int), SEEK_SET);
          fwrite(&n, sizeof(int), 1, f);
        }

    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                FILE *file;
                int pos; //position in linked list
              public:
                const_iterator(int i,FILE *fname){
                  cout<< "i: "<<i<<endl;
                  pos = i;
                  file = fname;
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
                  ++pos;
                  return *this;
                }
                const_iterator &operator--(){
                  --pos;
                  return *this;
                }
                const_iterator operator++(int){
                  const_iterator oldPos(pos, file);
                  ++pos;
                  return oldPos;
                }
                const_iterator operator--(int){
                  const_iterator oldPos(pos, file);
                  --pos;
                  return oldPos;
                }

                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname) //if file exist read size and freespace
        {
          cout<<"calling constructor"<<endl;
          f=fopen(fname.c_str(), "r+b");
          if(f!=nullptr){
            readSize(f);
            fseek(f, sizeof(int), SEEK_SET);
            fread(&freespace, sizeof(int), 1, f);
          } else {
            f = fopen(fname.c_str(), "w+b");
            writeSize(1, f);
            writeFreespace(1, f);
            writePrev(0, 0, f);
            writeNext(0, 0, f);

            //cout<< "filesize = "<< filesize<<endl;

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

        const_iterator insert(const_iterator position, const T &t)//writes node at first available freespace or at size if no valid freespace exists
        {
          cout<<"inserting at "<<position.pos<<endl;
          freespace = readFreespace(f);
          while (freespace > filesize){
            cout<<"freespace > filesize"<<endl;
            freespace = readNext(freespace, f);
            cout<<"freespace "<< freespace <<endl;
            cout<<"filesize: " << filesize<< endl;
          }
          cout<<"freespace = "<< freespace<<endl;
          const_iterator myNode(freespace, f);
          writeData(myNode.pos, t, f);
          writePrev(myNode.pos, readPrev(position.pos, f), f);//myNode->prev to --myNode->prev
          writeNext(myNode.pos, readNext(readPrev(position.pos, f), f), f);//myNode->next to --myNode->next
          writeNext(readPrev(myNode.pos, f), myNode.pos, f);//myNode->prev->next= myNode.pos
          writePrev(readNext(myNode.pos, f), myNode.pos, f);//myNode->next->prev=myNode.pos

         //  }
         //  cout<<"myNode.pos "<<myNode.pos<<endl;
         //  //fwrite(&t, sizeof(T); 1, f);
         //  writeData(myNode.pos, t, f);
         // cout<< "inserting at: " << myNode.pos << endl;
         //            //fseek(f, sizeof(int), SEEK_CUR);
         //  //fwrite(&readPrev(position.pos, f), sizeof(int), 1, f);
         //  writeNext(myNode.pos, position.pos, f);
         //  //fseek(f, sizeof(int), SEEK_CUR);
         //  //fwrite(&readNext(position.pos, f), sizeof(int), 1, f);
         //  writePrev(myNode.pos, readPrev(position.pos, f), f);
         //  cout<< "seting myNode -> prev to: " <<readPrev(position.pos, f)<<endl;
         //  writeNext(readPrev(myNode.pos, f), myNode.pos, f);
         //  cout<< "setting myNode.prev -> next to "<< myNode.pos << endl;
         //  writePrev(position.pos, myNode.pos, f);
          writeSize(filesize+1, f);
          return myNode;
        }
        T operator[](int index) const{
          cout<<"[] called on "<<index<<endl;
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
