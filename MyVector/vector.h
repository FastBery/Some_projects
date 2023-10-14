#pragma once
#include <iostream>
#include <cstddef>
#include <algorithm>

template<typename T>
class vector
{
    T *ptr;
    std::size_t s, cap;

    void reallocate(std::size_t n);

public:

    using value_type = T;
    using size_type = std::size_t;

    using reference  = T &;
    using const_reference  = T const &;

    using iterator = T *;
    using const_iterator = T const *;
    
    ~vector()
    {
        for(std::size_t i = 0; i < this->s; ++i)
            (ptr + i)->~T();
        std::free(ptr);
    }
    vector()
        : ptr(nullptr)
        , s(0)
        , cap(0)
    {}
    vector(std::size_t n)
        : vector<T>()
    {
        resize(n);
    }
    vector(vector<T> const &x)
        : vector<T>()
    {
        reallocate(x.s);
        this->s= x.s;
        for(std::size_t i = 0; i < x.s; i++){
            new (ptr + i) T(x[i]);
        }
    }
    vector(vector<T>      &&x) 
        : ptr(x.ptr)
        , s(x.s)    
        , cap(x.cap)
    {
        new (&x) vector<T>();
    }

    template<typename It>
    vector(It first, It last)
        : vector<T>()
    {
        insert(ptr, first, last);
    }

    vector(std::initializer_list<T> list)//{}
        : vector<T>()
    {
        std::size_t n = list.size();
        resize(n);
        for (std::size_t i = 0; i < n; i++){
            new (ptr + i) T(static_cast<T>(*(list.begin() + i)));
        }
        this->s = n;
    }

    vector<T> &operator=(vector<T> const &other)//copy
    {
        if( this != &other){
            this->~vector<T>();
            new (this) vector<T>(other);
        }
        return *this;
    }

    vector<T> &operator=(vector<T>      &&other)//move
    {
        if( this != &other){
            this->~vector<T>();
            new (this) vector<T>(static_cast<vector<T> &&>(other));
        }
        return *this;
    }

    vector<T> &operator=(std::initializer_list<T> list)
    {
        new (this) vector<T>(list);
        return *this;
    }

    bool operator==(const vector<T> &other) const {
        if(this->s== other.s){
            for(std::size_t i = 0; i < this->s; i++){
                if( ptr[i] != other.ptr[i] ){
                    return 0;
                }
            }
            return 1;
        }
        else{
            return 0;
        }
    }

    bool operator!=(const vector<T> &other) const {
        return !(other == this);
    }

    bool operator<(const vector<T> &other) const {
        std::size_t n = other.s;
        if(*this != other){
            if(n < this->s){
                for(std::size_t i = 0; i < n; i++){
                    if(other.ptr[i] > ptr[i]){
                        return 1;
                    }
                    else{
                        if(ptr[i] > other.ptr[i]){
                            return 0;
                        }
                    }
                }
                return 0;
            }
            else{
                for(std::size_t i = 0; i < this->s; i++){
                    if(other.ptr[i] > ptr[i]){
                        return 1;
                    }
                    else{
                        if(ptr[i] > other.ptr[i]){
                            return 0;
                        }
                    }
                }
                return 0;
            }
        }
        else{
            return 0;
        }
    }

    bool operator>(const vector<T> &other) const {
        if(this < other or this == other){
            return 0;
        }
        else{
            return 1;
        }
    }

    bool operator<=(const vector<T> &other) const {
       if(*this < other) {return 1;}
       if(*this == other){return 1;}
       return 0;
    }

    bool operator>=(const vector<T> &other) const {
        if(*this > other) {return 1;}
        if(*this == other){return 1;}
        return 0;
    }

    T       *begin()       {return ptr;}
    T       *  end()       {return ptr + this->s;}
    T const *begin() const {return ptr;}
    T const *  end() const {return ptr + this->s;}

    void push_back(T const &da)
    {
        if(this->s== cap)
            reallocate(cap == 0 ? 1 : 2 * cap);
        new (ptr + this->s++) T(da);
    }

    T       &front()       {return *ptr;}
    T const &front() const {return *ptr;}

    T       &back()       {return ptr[this->s- 1];}
    T const &back() const {return ptr[this->s- 1];}

    T       *data()       {return ptr;}
    T const *data() const {return ptr;}
    
    T       &operator[](std::size_t n)       {return ptr[n];}
    T const &operator[](std::size_t n) const {return ptr[n];}
    T       &operator[](int n)       {return ptr[n];}
    T const &operator[](int n) const {return ptr[n];}

    T       &at(std::size_t n)       {return ptr[n];}
    T const &at(std::size_t n) const {return ptr[n];}
    
    T       *rbegin()       {return ptr + this->s;}
    T       *  rend()       {return ptr;}
    T const *rbegin() const {return ptr + this->s;}
    T const *  rend() const {return ptr;}

    bool empty() const {return this->s== 0;}

    std::size_t size() const {return this->s;}

    std::size_t max_size() const {return cap;}

    void reserve(std::size_t new_cap){
        if(new_cap > cap)
            reallocate(new_cap);
    }

    // void resize(size_type count){
    //     size_type n = size_type(end() - ptr) + count;
    //     for(size_type i = 0; i < n; i++){
    //         (end() - i - 1)->~T();
    //     }
    //     s -= count;
    // }

    void resize(size_type count){
        if(count < s){
            erase(begin() + count - 1, end());
        }
        else{
            if(s < count){
                reallocate(count);
                insert(end(), count - s, 0);
            }
        }
        s = count;
    }

    std::size_t capacity() const {return cap;}

    void shrink_to_fit(){
        reallocate(s);
    }

    // void erase(T *pos){
    //     std::size_t n = std::size_t(this->end() - pos);
    //     for(std::size_t i = 0; i < n - 1; i++){
    //         pos[i] = static_cast<T &&>(pos[i + 1]);
    //     }
    //     (this->end() - 1)->~T();
    //     this->s--;
    // }

    //     iterator erase(const_iterator pos){
    //     std::size_t n = std::size_t(this->end() - pos);
    //     for(std::size_t i = 0; i < n - 1; i++){
    //         pos[i] = static_cast<T &&>(pos[i + 1]);
    //     }
    //     (this->end() - 1)->~T();
    //     this->s--;
    //     if(end() - pos == 1){
    //         return end();
    //     }
    //     else{
    //         return pos;
    //     }
    // }

    iterator erase(T *a, T *b){
        if(b == a){
            return b;
        }
        if(b == end()){
            std::size_t n = std::size_t(this->end() - a);
            for(size_type i = 0; i < n; i++){
                (this->end() - i - 1)->~T();
            }
            s -= n;
            return end();
        }
        std::size_t n = std::size_t(this->end() - b);
        for(std::size_t i = 0; i < n; i++){
            a[i] = static_cast<T &&>(b[i]);
        }
        for(std::size_t i = 0; i < std::size_t(b - a); i++){
            (this->end() - i - 1)->~T();
        }
        this->s -= std::size_t(b - a);
        return a;
    }

    iterator erase(const_iterator pos){
        return erase(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1);
    }

    void clear(){
        erase(begin(), end());
    }

    // void pop_back(){
    //     (ptr + this->s- 1)->~T();
    //     this->s--;
    // }

    void pop_back(){
        erase(end());
    }

    // template<typename It>
    iterator insert(const_iterator pos, const std::size_t &count, const T &value){
        if(count == 0){
            return const_cast<iterator>(pos);
        }
        std::size_t n = std::size_t(pos - ptr);
        if((this->s+ count) > cap){
            reallocate(cap + count);
        }
        for (std::size_t i = 0; i < count; i++){
            new (ptr + this->s+ i) T();
        }

        T *newpos = ptr + n;

        for(std::size_t i = 0; i < std::size_t(this->end() - newpos); i++){
            ptr[this->s- i + count - 1] = static_cast<T &&>(ptr[this->s- i - 1]);
        }

        for(std::size_t i = 0; i < count; i++){
            newpos[i] = value;
        }
        // ptr[s] = value;

        this->s += count;
        return const_cast<iterator>(pos - count);
    }

    iterator insert(const const_iterator pos, T &&value){
        return insert(pos, 1, static_cast<T &&>(value));
    }

    iterator insert(const iterator pos, const T &value){
        return insert(pos, 1, value);
    }

    template<typename It>
    iterator insert(const iterator pos, const It first, const It last){
        if(first == last){
            return pos;
        }
        iterator beforepos = pos - 1;
        std::size_t n = std::size_t(pos - ptr);
        std::size_t m = std::size_t(last - first);
        if((this->s+ m) > cap){
            reallocate(cap + m);
        }
        for (std::size_t i = 0; i < m; i++){
            new (ptr + this->s+ i) T();
        }

        T *newpos = ptr + n;

        for(std::size_t i = 0; i < std::size_t(this->end() - newpos); i++){
            ptr[this->s- i + m - 1] = static_cast<T &&>(ptr[this->s- i - 1]);
        }

        for(std::size_t i = 0; i < m; i++){
            auto now = *(first + i);
            newpos[i] = now;
        }

        this->s += m;
        return beforepos;
    }



    iterator insert(const T *pos, const std::initializer_list<T> list){
        size_type n = size_type(list.size());
        if(n == 0){
            return pos;
        }
        return insert(pos, list.begin(), list.end());
    }

    void swap(vector<T> &other){
        std::swap(ptr, other.ptr);
        std::swap(s, other.s);
        std::swap(cap, other.cap);
    }

    template<typename... Args>
    T *emplace(const T *pos, Args &&... args){
        std::size_t n = std::size_t(pos - ptr);


        if(this->s== cap){
            reallocate(cap == 0 ? 1 : 2 * cap);
        }

        new (ptr + this->s) T();

        T *newpos = ptr + n;
        if(s != 0){
            for(std::size_t i = 0; i < std::size_t(this->end() - newpos); i++){
                ptr[this->s- i] = static_cast<T &&>(ptr[this->s- i - 1]);
            }
        }
        (ptr + n)->~T();
        new (ptr + n) T(std::forward<Args &&>(args)...);
        // ptr[n] = T(static_cast<Args &&...>(args...));

        // ptr[s] = value;

        this->s++;
        return (ptr + n);
    }

    template<typename... Args>
    T *emplace_back(Args &&... args){
        return emplace(end(), std::forward<Args &&>(args)...);
    }

    void assign(std::size_t count, const T &value){//works
        clear();
        if(count > cap){
            reallocate(count);
        }
        insert(ptr, count, value);
    }

    void assign(const T *first, const T *last){
        clear();
        std::size_t n = std::size_t(last - first);
        if(n > cap){
            reallocate(n);
        }
        insert(ptr, first, last);
    }

    void assign(std::initializer_list<T> list){//works
        clear();
        std::size_t n = std::size_t(list.size());
        if(n > cap){
            reallocate(n);
        }
        insert(ptr, list);
    }
};

template<typename T>
void vector<T>::reallocate(std::size_t n){
    T *newptr = static_cast<T *>(std::malloc(sizeof(T)*n));
    for(std::size_t i=0; i<s; i++){
        new (newptr + i) T(static_cast<T &&>(ptr[i]));
        (ptr + i)->~T();
    }   
    std::free(ptr);
    ptr = newptr;
    cap = n;
}
