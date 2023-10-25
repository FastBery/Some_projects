#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using u = int;


class inf : public std::vector<u>
{
    static std::vector<u> sum_of_2(u a, u b){
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

    static std::vector<u> sum_of_2_vectors(inf a, inf b){
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
        // inf ans;
        // ans.vec = answer;
        return answer;
    }

    static u get_sign(std::vector<u> const &a){return a.front() < 0 ? -1 : 1;}

    static std::vector<u> dif_of_2_vectors(std::vector<u> a, std::vector<u> b){
        u sign_a = get_sign(a), sign_b = get_sign(b);
        if(sign_a == -1 and sign_b == 1){
            a.front() *= -1;
            auto answer = sum_of_2_vectors(a, b);
            answer.front() *= -1;
            return answer;
        }
        if(sign_a == 1 and sign_b == -1){
            b.front() *= -1;
            return sum_of_2_vectors(a, b);
        }
        if(sign_a == -1 and sign_b == -1){
            b.front() *= -1;
            a.front() *= -1;
            auto answer = dif_of_2_vectors(b, a);
            return answer;
        }
        if(max_of_2(a, b) == a){
            b.front() *= -1;
            return sum_of_2_vectors(a, b);
        }
        else{
            a.front() *= -1;
            auto answer = sum_of_2_vectors(b, a);
            answer.front() *= -1;
            return answer;
        }
    }
    
    static std::vector<u> max_of_2(std::vector<u> a, std::vector<u> b){
        std::vector<u> answer;
        if(a.size() != b.size()){
            if(a.size() > b.size()){
                return a;
            }
            else{
                return b;
            }
        }
        else{
            for(int i = 0; i < a.size(); i++){
                if(abs(a[i]) > abs(b[i])){
                    return a;
                }
                else{
                    return b;
                }
            }
        }
        return answer;
    }

public:
    inf() = default;
    inf(std::vector<u> const &v)
        : std::vector<u>(v)
    {}
    inf(std::string str)
    {
        u sign = 1;
        std::size_t size = str.size();
        if(str[0] == '-'){
            size--;
            sign = -1;
        }
        std::size_t n = size/4;
        for(std::size_t i = 0; i < n; i++){
            u num = 0;
            for(std::size_t j = 0; j < 4; j++){
                // num.insert(num.begin(), str[size - i*4 - j - 1] - 48);
                num += pow(10, j)*(str[size - i*4 - j - 1] - 48);
            }
            insert(begin(), num);
        }
        u num = 0;
        for(std::size_t i = 0; i < size - 4*n; i++){
            num += pow(10, i)*(str[size - 4*n - i - 1] - 48);
        }
        insert(begin(), num);
        front() *= sign;
    }

    inf operator+(inf const &other){
        return {sum_of_2_vectors(*this, other)};
    }

    inf operator-(inf const &other){
        return {dif_of_2_vectors(*this, other)};
    }
};

std::ostream &operator<<(std::ostream& os, inf const &a){
    for(std::size_t i = 0; i < a.size(); i++){
        os << a[i];
    }
    return os;
}
