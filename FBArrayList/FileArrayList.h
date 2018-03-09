#ifndef FileArrayList_h
#define FileArrayList_h
//#include<iostream>
// using std::cout;
// using std::endl;

template<typename T>
class FileArrayList {
       FileArrayList(const FileArrayList<T> &that) = delete;
       FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

        // TODO - Your private data.

        //readfile(int index)
        T read(int index)const{
          fseek(f, (sizeof(int)+index*sizeof(T)), SEEK_SET);
          T retval;
          fread(&retval, sizeof(T), 1, f);
          // cout<< retval <<endl;
          return retval;
        }

        void write(int index, T data){
          //T *val = &data;
          // cout<<"index: "<< index <<" data: "<< data <<endl;
          fseek(f, sizeof(int)+index*sizeof(T), SEEK_SET);
          fwrite(&data, sizeof(T), 1, f);
        }
        //writefile(int index)

        FILE *f;
        int sz;
        // TODO - Private helper functions. (Maybe file IO with an index.)

    public:
        typedef T value_type;

        class const_iterator {
                // TODO - Your private data.
                int i;
                FILE *filename;
            public:
                const_iterator(int integer,FILE *file){
                  i = integer;
                  filename = file;
                }
                const_iterator(const const_iterator &other){
                  i=other.i;
                  filename=other.filename;
                }
                T operator*(){
                  T temp;
                  fseek(filename, sizeof(int)+i*sizeof(T), SEEK_SET);
                  fread(&temp, sizeof(T), 1, filename);
                  return temp;
                } //read from file, return data of type T
                bool operator==(const const_iterator &other) const{
                  return i==other.i && f==other.filename;
                }
                bool operator!=(const const_iterator &other) const{
                  return i!=other.i || f!=other.filename;
                }
                const_iterator &operator=(const const_iterator &other){
                  f = other.filename;
                  i = other.i;
                  return *this;
                }
                const_iterator &operator++(){
                  i+=1;
                  return *this;
                }
                const_iterator &operator--(){
                  i-=1;
                  return *this;
                }
                const_iterator operator++(int){
                  i+=1;
                  return *this;
                }
                const_iterator operator--(int){
                  i-=1;
                  return *this;
                }

                friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname){
          f=fopen(fname.c_str(), "r+b");
          if(f!=nullptr){
            //FIXME File exists
            fseek(f,0, SEEK_SET);
            fread(&sz, sizeof(int), 1, f);
          } else{
            f = fopen(fname.c_str(), "w+b");
            sz = 0;
            fseek(f,0, SEEK_SET);
            fwrite(&sz, sizeof(int), 1, f);
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
            f=fopen(fname.c_str(),"w+b");
            sz = 0;
            for(auto itr=begin; itr!=end; ++itr){
              push_back(*itr);
            }
        }
        ~FileArrayList(){
          fseek(f, sizeof(int), SEEK_SET);
          fwrite(&sz, sizeof(int), SEEK_SET, f);
          fclose(f);
        }
        void push_back(const T &t){
          write(sz, t);
          ++sz;
        }
        void pop_back(){
          --sz;
        }
        int size() const{
          return sz;
        }
        void clear(){
          sz = 0;
        }
        const_iterator insert(const_iterator position, const T &t){
          for(int i = sz; i > position.i; --i){
            write(i+1, read(i));
          }
          write(position.i, t);
          ++sz;
          return position;
        }
        T operator[](int index) const{
          T retval = read(index);
          return retval;
        }
        const_iterator erase(const_iterator position){
          if(position.i == sz){
            --sz;
          } else {
            for(int i = position.i; i < sz;++i){
              write(i, read(i+1));
            }
            --sz;
          }
          return position;
        }
        void set(const T &value,int index){
            write(index, value);
        }
        const_iterator begin(){
          return const_iterator(0, f);
        }
        const_iterator begin() const{
          return const_iterator(0, f);
        }
        const_iterator end(){
          return const_iterator(sz, f);
        }
        const_iterator end() const{
          return const_iterator(sz, f);
        }
        const_iterator cbegin() const{
          return const_iterator(0, f);
        }
        const_iterator cend() const{
          return const_iterator(sz, f);
        }
};
#endif
