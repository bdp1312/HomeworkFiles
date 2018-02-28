template<typename T>
class FileArrayList {
        FileArrayList(const FileArrayList<T> &that) = delete;
        FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

        // TODO - Your private data.

        //readfile(int index)
        T read(int index)const{
          fseek(f, sizeof(T), index, f);
          T retval;
          fread(&retval, sizeof(T), 1, f);
          return retval;
        }

        void write(int index, T data){
          fseek(f, sizeof(T), index, f);
          fwrite(data, sizeof(T), SEEK_SET);
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
                FILE *f;
            public:
                const_iterator(int integer,FILE *file){
                  i = integer;
                  f = file;
                }
                const_iterator(const const_iterator &other){
                  i=other.i;
                  f=other.f;
                }
                T operator*(){
                  fseek(f, sizeof(int)+i*sizeof(T), SEEK_SET);
                  fread(&temp, sizeof(T), 1,1f);
                  return temp;
                } //read from file, return data of type T
                bool operator==(const const_iterator &other) const{
                  return i==other.i && f==other.f;
                }
                bool operator!=(const const_iterator &other) const{
                  return i!=other.i || f!=other.f;
                }
                const_iterator &operator=(const const_iterator &other){
                  f = other.f;
                  i = other.i;
                }
                const_iterator &operator++(){
                  i+=1;
                }
                const_iterator &operator--(){
                  i-=1;
                }
                const_iterator operator++(int)
                  i+=1;
                const_iterator operator--(int){
                  i-=1;
                }

                friend class FileArrayList;
        };

        // General Methods
        FileArrayList(const std::string &fname){
          f = fopen(fname.c_str(), "r+b")
          if(f!=nullptr){
            //FIXME File exists
            fseek()
            fread()
          } else{
            f = fopen(fname.c_str(), "w+b")
            sz = 0;
            fseek(f,0, SEEK_SET);
            fwrite(&sz,siveof(int),1,f);
          }
        }

        template<typename I>  // The type I will be an iterator.
        FileArrayList(I begin,I end,const std::string &fname) {
            // TODO - Write this one here. It is easier than trying to fight with adding a template below.
            f=fopen(fname.cst(),"w+b");
            sz = 0;
            for(auto itr=begin; itr!=end; ++itr){
              push_back(*itr);
            }
        }
        ~FileArrayList();
        void push_back(const T &t){
          write(sz+1, t);
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
          for(int i = sz; sz > position.i; --i){
            write(i+1, read(i))
          }
          write(position.i, t);
          ++sz;
          return position;
        }
        T operator[](int index) const{
          return read(index);
        }
        const_iterator erase(const_iterator position){
          for(int i=position.i; i<sz; ++i){
            write(i, read(i+1));
          }
          --sz;
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
