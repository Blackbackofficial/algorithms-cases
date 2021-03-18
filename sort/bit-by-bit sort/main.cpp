// Ввести массив с клавиатури и отсортировать поразрядной сортировкой на векторах

#include "iostream"
#include "vector"
#include "cmath"

int main() {
    int num, width, pr;
    std::vector<int> array;// инициализация дополнительных списков - "карманов"
    std::vector <std::vector<int>> arr;
    std::cout << "Введите сорт. массив" << std::endl;
    while(std::cin >>num) {
        array.push_back(num);
    }
    std::cout << "Введите сорт. массив" << std::endl;
    std::cin >> width;

    for (int i = 0; i < 10; ++i) {
        arr.emplace_back();
    }


    // Поразрядная сортировка
    for (int i = 0; i < width; i++) {
        int per = pow(10, i+1);
        int del = pow(10, i);
        for (int j : array) {
            pr = j % per / del;
            pr = pr;
            arr[pr].push_back(j);
        }
        pr = pr;

        int k = 0; // индекс элементов новой последовательности
        for (int j = 0; j < arr.size(); j++) {
            if (!arr[j].empty()) {
                for (int q = 0; q < arr[j].size(); q++) {
                    array[k++] = arr[j][q];
                }
                arr[j].clear();
            }
        }
    }

    for (int i : array) {
        std::cout << i << " ";
    }
    return 0;
}

