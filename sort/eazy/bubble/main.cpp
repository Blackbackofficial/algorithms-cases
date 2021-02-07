// Ввести массив с клавиатури и отсортировать пузырьковым методом и улучшенным пузырьком

#include "iostream"
#include "vector"

int main() {
    std::vector<int> array;
    std::vector<int> arr2;
    std::vector<int> arr3;
    int num;
    while (std::cin >> num) {
        array.push_back(num);
    }

    arr2 = array;
    arr3 = array;

    // Сортировка пузырьком
    for (int i = 0; i < arr2.size(); ++i) {
        for (int j = 0; j < arr2.size(); ++j) {
            if (arr2[i]<arr2[j] && i != j) { // сейчас по неубыванию, поменяй знак если нужно по убыванию
                int safe = arr2[i];
                arr2[i] = arr2[j];
                arr2[j] = safe;
            }
        }
    }

    for (auto i : arr2) {
        std::cout << i << " ";
    }

    // Сортировка оптимизированным пузырьком
    for (int i = 0; i < arr3.size(); ++i) {
        bool flag = true;
        for (int j = 0; j < arr3.size(); ++j) {
            if (arr3[i]<arr3[j] && i != j) { // сейчас по неубыванию, поменяй знак если нужно по убыванию
                flag = false;
                std::swap(arr3[i],arr3[j]);
            }
        }
        if (flag) {
            break;
        }
    }

    for (auto j : arr3) {
        std::cout << j << " ";
    }

    return 0;