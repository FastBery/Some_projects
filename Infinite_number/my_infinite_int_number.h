#pragma once
#include <iostream>
#include <vector>
#include <string>

using u = int;


class inf
{
    std::vector<u> vec;
    /* if True number < 0; if False number >= 0*/
public:
    ~inf()
    {
        vec.clear();
    }

    inf()
        : vec()
    {}

    inf(std::string str)
        : vec()
    {
        vec = string_to_vector(str);
    }

    std::vector<u> string_to_vector(std::string str){
        std::size_t size = str.size();
        std::size_t n = size/4;
        std::vector<u> answer;
        for(std::size_t i = 0; i < n; i++){
            std::vector<u> num;
            for(std::size_t j = 0; j < 4; j++){
                num.insert(num.begin(), str[size - i*4 - j - 1] - 48);
            }
            answer.insert(answer.begin(), num.begin(), num.end());
        }
        std::vector<u> num;
        for(std::size_t i = 0; i < size - 4*n; i++){
            num.insert(num.begin(), str[size - 4*n - i - 1] - 48);
        }
        answer.insert(answer.begin(), num.begin(), num.end());
        return answer;
    }

    inf &operator+(inf &other){
        inf answer = sum_of_2_vectors(this->vec, (&other)->vec);
        return answer;
    }

    std::vector<u> sum_of_2(u a, u b){
        std::vector<u> vec = {0, 0};
        if(a >= 10000 or b >= 10000){
            throw std::invalid_argument("received numbers higher or equal than 10^5");
        }
        u c = a + b;
        if(c >= 10000){
            vec[0]++;
            vec[1] = c%10000;
        }
        else{
            if(c < 0){
                vec[0] = -1;
                vec[1] = 10000 + c;
            }
            else{
                vec[1] = c;
            }
        }
        return vec;
    }

    std::vector<u> sum_of_2_vectors(std::vector<u> a, std::vector<u> b){
        u sign = 1;
        if(b.front() < 0){
            sign = -1;
            b.front() *= -1;
        }
        //making the same size
        int max_len = std::max(a.size(), b.size());
        if(a.size() != b.size()){
            if(a.size() != max_len){
                for(int i = 0; i < max_len - a.size(); i++){
                    a.insert(a.begin(), 0);
                }
            }
            else{
                for(int i = 0; i < max_len - b.size(); i++){
                    b.insert(b.begin(), 0);
                }
            }
        }
        std::vector<u> answer;
        std::vector<u> temp;
        u x = 0;
        for(int i = 0; i < max_len; i++){
            temp = sum_of_2(*(a.end() - i - 1), (*(b.end() - i - 1))*sign);
            auto y = sum_of_2(temp[1], x);
            if( y[0] == 1){
                answer.insert(answer.begin(), y[1]);
                x = temp[0] + 1;
            }
            else{
                    answer.insert(answer.begin(), y[1]);
                    x = temp[0];
            }
        }

        for(int i = 0; i < answer.size(); i++){
            if(answer[i] != 0){
                if(i != 0){
                    answer.erase(answer.begin(), answer.begin() + i);
                }
                else{break;}
            }
        }
        if(x != 0){
            answer.insert(answer.begin(), x);
        }
        inf ans;
        ans->vec = answer;
        return ans;
    }
};

// template<typename T>
// void inf<T>::reallocate(u64 size){
//     T *newptr = static_cast<T *>(std::malloc(sizeof(char)*size));
//     for(u64 i = 0; i < size; i++){
//         new (newptr + i) char(static_cast<T &&>(ptr[i]));
//         (ptr + i)->~ char();
//     }
//     std::free(ptr);
//     ptr = newptr;
// }