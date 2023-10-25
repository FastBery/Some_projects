#include "my_infinite_int_number.h"
#include <iostream>

using namespace std;

// std::vector<u> string_to_vector(std::string str){
//         std::size_t size = str.size();
//         std::size_t n = size/4;
//         std::vector<u> answer;
//         for(std::size_t i = 0; i < n; i++){
//             u num = 0;
//             for(std::size_t j = 0; j < 4; j++){
//                 // num.insert(num.begin(), str[size - i*4 - j - 1] - 48);
//                 num += pow(10, j)*(str[size - i*4 - j - 1] - 48);
//             }
//             answer.insert(answer.begin(), num);
//         }
//         u num = 0;
//         for(std::size_t i = 0; i < size - 4*n; i++){
//             num += pow(10, i)*(str[size - 4*n - i - 1] - 48);
//         }
//         answer.insert(answer.begin(), num);
//         return answer;
//     }

int main(){
    inf a = inf("-123455");
    inf b = inf("543211");
    // a = {1, 2342} + {2, 2102};
    // for(std::size_t i = 0; i < 2; i++){
    //     cout << a[i];
    // }
    cout << a.size() << endl;
    // vector<u> vec = string_to_vector("123456");
    // for(auto now : vec){
    //     cout << now << " ";
    // }
    cout << a[0] << " " << a[1] << endl;
    cout << b[0] << b[1] << endl;
    inf c;
    c = b - a;
    cout << c[0] << c[1] << endl;
    // inf c = a + b;
    cout << c[0] << c[1] << endl;
}
