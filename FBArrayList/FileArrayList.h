template<typename T>
class FileArrayList {
        FileArrayList(const FileArrayList<T> &that) = delete;
        FileArrayList<T> operator=(const FileArrayList<T> &that) = delete;

        // TODO - Your private data.

        //readfile(int index)
        T Read(int index)const{
          fseek(...)
          fread(...)
        }

        void Write(int index, T data){
          fseek(...)
          fwrite(...)
        }
        //writefile(int index)

        FILE *f;
        int size;
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
            for(auto itr=begin; iter!=end; ++itr){

            }
        }
        ~FileArrayList();
        void push_back(const T &t);
        void pop_back();
        int size() const;
        void clear();
        const_iterator insert(const_iterator position, const T &t);
        T operator[](int index) const;
        const_iterator erase(const_iterator position);
        void set(const T &value,int index);

        const_iterator begin();
        const_iterator begin() const;
        const_iterator end();
        const_iterator end() const;
        const_iterator cbegin() const;
        const_iterator cend() const;
};
