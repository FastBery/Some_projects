#pragma once
#include <iostream>
#include <string>

using u64 = std::size_t;

// template<typename T>
class inft
{
    char *ptr;
    u64 N;
    bool sign;
    std::string number;
    /* if True number < 0; if False number >= 0*/
    void reallocate(u64 size);
public:
    ~inft()
    {
        for(u64 i = 0; i < this->N; i++){
            (ptr + i)->~char;
        }
        free(ptr);
    }

    inft()
        : ptr(nullptr)
        , N(0)
        , sign(false)
        , number()
    {}

    inft(u64 size)
        : inft()
    {
        reallocate(size);
    }

    inft(inft &num)
        : inft()
    {
        reallocate(num.N);
        for(u64 i = 0; i < this->N; i++){
            new (ptr + i) char(static_cast<T &&>(num.ptr[i]));
        }
    }
};

// template<typename T>
void inft<int>::reallocate(u64 size){
    T *newptr = static_cast<T *>(std::malloc(sizeof(char)*size));
    for(u64 i = 0; i < size; i++){
        new (newptr + i) char(static_cast<T &&>(ptr[i]));
        (ptr + i)->~T();
    }
    std::free(ptr);
    ptr = newptr;
}