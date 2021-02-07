// Дан одномерный массив, длину массива задаёт пользователь.
// Вычислить сумму квадратов тех чисел, модуль которых превышает значение 2,5.

#include "iostream"
#include "vector"
#include <cmath>

int main() {
    float x;
    std::vector<float> mass;
    std::vector<float> endmass;
    std::cout << "Введите массив, введите | что бы закончить" << std::endl;
    while (std::cin >> x) {
        mass.push_back(x);
    }
    for (int j = 0; j < mass.size(); j++) {
        if (abs(mass[j]) > 2.5) {
            endmass.push_back(pow(abs(mass[j]),2));
        }
    }

    for (int j = 0; j < endmass.size(); j++) {
        x += endmass[j];
    }

    for (float mas : endmass) {
        std::cout << mas << std::endl;
    }

    std::cout << "Сумма квадратов равна: " << x << std::endl;
    return 0;
}