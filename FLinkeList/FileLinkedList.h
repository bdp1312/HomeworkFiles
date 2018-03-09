#ifndef FileArrayList_h
#define FileArrayList_h
template<typename T>
class FileLinkedList {
        FileLinkedList(const FileLinkedList<T> &that) = delete;
        FileLinkedList<T> operator=(const FileLinkedList<T> &that) = delete;

        // TODO - Your private data.

        FILE *f;
        int size; //number of nodes
        int freespace; //pointer to unalocated node, ==-1 if none exist
        int nodeSize = sizeof(T)=sizeof(int)*2;//size of node

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
          } else {
            fseek(f, node + sizeof(T), SEEK_SET);
          }
          fread(f, &temp, sizeof(int),1,f);
          return temp;
        }
        //determines location of the next node
        int readNext(int node, FILE *f){
          int temp;
          if(node==0;){
            fread
          }
          fseek(f, node+sizeof(T)+sizeof(int), SEEK_SET);
          fread(f, &temp, sizeof(int),1,f);
          return temp;
        }
        void writePrev(int node, int pos){
          fseek(f, node + sizeof(T), SEEK_SET);
          fwrite(&pos, sizeof(int), 1, f);
        }
        void writeNext(int node, int pos){
          fseek(f, node+sizeof(T)+sizeof(int), SEEK_SET);
          fwrite(&pos, sizeof(int), 1, f);
        }
    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                FILE *file;
                int pos; //holds location of node in file
            public:
                const_iterator(int i, FILE *f){
                  pos = i*nodeSize;
                  file = f;
                }
                const_iterator(const const_iterator &i){
                  pos = i.pos;
                  file = i.file;
                }
                T operator*(){
                  T temp;
                  fseek(f, pos, SEEK_SET);
                  fread(&temp, sizeof(T), 1, f);
                  return T;
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
                  pos = readNext(pos);
                  return *this;
                }
                const_iterator operator--(int){
                  pos=readPrev(pos)
                  return *this;
                }

                friend class FileLinkedList;
        };

        // General Methods
        FileLinkedList(const std::string &fname){
          f=fopen(fname.c_str(), "r+b");
          size=0;
          if(f!=nullptr){
            const_iterator i = begin();
            size = 1
            while(ReadNext(i.pos) != 0){
              i.pos = ReadNext(i.pos);
              ++size;
            }
          } else {
            f = fopen(fname.c_str(), "w+b");
            size = 0;
            freespace=-1;
            f
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileLinkedList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.

        }
        ~FileLinkedList(){
          fclose();
        }

        void push_back(const T &t) { insert(end(),t); }
        void pop_back() { erase(--end()); }
        int size() const{return size;}
        void clear() { while (size()>0) pop_back(); }

        const_iterator insert(const_iterator position, const T &t){
          if(size = 0){
            fwrite(&t, sizeof(T), 1, f);
            writeNext(0, )
            writeNext()
          }
          fseek(f, position.pos*nodeSize(), SEEK_SET);


        }
        T operator[](int index) const{
            auto itr=begin();
            for (int i=0;i<index;++i){
              iter.pos = readNext(iter.pos);            }
            }
            return *itr;
        }
        const_iterator erase(const_iterator position);
        void set(const T &value,int index){
          auto iter = begin();
          for(int i = 0; i<index;++i){
            iter.pos = readNext(iter.pos);
          }
          fseek(f, iter.pos, SEEK_SET);
          fwrite(&value, sizeof(T), 1, f);
        }
        void set(const T &value,const_iterator position){
          fseek(f, position.pos, SEEK_SET);
          fwrite(&value, sizeof(T), 1, f);
        }

        const_iterator begin(){
          return const_iterator(readNext(0), f);
        }
        const_iterator begin() const{
          return const_iterator(readNext(0), f);
        }
        const_iterator end(){
          return const_iterator(size, f);
        }
        const_iterator end() const{
          return const_iterator(size, f);
        }
        const_iterator cbegin() const{
          return const_iterator(readNext(0), f);
        }
        const_iterator cend() const{
          return const_iterator(size*, f)
        }
};
#endif
