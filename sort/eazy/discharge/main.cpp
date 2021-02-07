// Составить алгоритм определяющий, есть ли среди цифр введенного трехзначного числа — одинаковые.
// Число вводится с клавиатуры.

#include "iostream"
#include "vector"

int main() {
    int num;
    bool flagZero, flag = false;
    std::vector<int> massD;
    int del[] = {10000, 1000, 100, 10, 1};
    std::cin >> num;
    for (int i = 0; i < 5; ++i) {
        if ((num / del[i]) % 10 != 0 && !flagZero){
            flagZero = true;
        }
        if (flagZero) {
            massD.push_back((num / del[i]) % 10);
        }
    }
    for (int j = 0; j < massD.size(); ++j) {
        for (int i = 0; i < massD.size(); ++i) {
            if (massD[j] == massD[i] && j != i) {
                flag = true;
                break;
            }
        }
    }

    (flag) ? std::cout << "Есть" : std::cout << "Нету";
    return 0;
}