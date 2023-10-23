#include <iostream>
#include <vector>

using namespace std;
using u = int;

//summ of two "u"
// НЕ ТРОГАТЬ
vector<u> sum_of_2(u a, u b){
    vector<u> vec = {0, 0};
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

vector<u> max_of_2(vector<u> a, vector<u> b){
    vector<u> answer;
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

// summ of two vectors 
// НЕ ТРОГАТЬ
vector<u> sum_of_2_vectors(vector<u> a, vector<u> b){
    u sign = 1;
    if(b.front() < 0){
        sign = -1;
        b.front() *= -1;
    }
    //making the same size
    int max_len = max(a.size(), b.size());
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
    vector<u> answer;
    vector<u> temp;
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
    return answer;
}

u get_sign(vector<u> a){return a.front() < 0 ? -1 : 1;}

vector<u> dif_of_2_vectors(vector<u> a, vector<u> b){
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

vector<u> string_to_vector(string str){
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
int main(){
    // vector<u> b = {-2, 5000};
    // vector<u> a = {-3,5000};
    // auto c = dif_of_2_vectors(a, b);
    // for(auto now : c){
    //     cout << now;
    // }
    // int c = '9' - 48;
    // cout << endl;
    // cout << c;
    vector<u> vec = string_to_vector("2");
    for(auto now : vec){
        cout << now;
    }
}