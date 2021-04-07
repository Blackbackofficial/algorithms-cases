/*
 * Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую
 * статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве.
 * 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

struct cmp {
    bool operator()(const int& left, const int& right)  {return left > right;}
};

int random(int left, int right) {
    int el = left + rand() % (right - left);
    return el;
}

template <typename T, class CMP>
int partition(T * mass, int left, int right, CMP cmp)
{
    if (right - left <= 1)
        return 0;
    int el = random(left, right);
    if (el != right - 1)
        std::swap(mass[el], mass[right - 1]);

    int i = left;
    int j = left;

    while (j != right - 1) {
        if (cmp(mass[j], mass[right - 1]))
            j++;
        else {
            std::swap(mass[i], mass[j]);
            j++;
            i++;
        }
    }

    std::swap(mass[i], mass[right - 1]);
    return i;
}

template<typename T, class CMP>
void find_k_static(T * mass, int n, int k, CMP cmp) {
    int left = 0, right = n;

    int pos = partition(mass, left, right, cmp);
    do {
        if (pos > k) {
            right = pos;
        } else {
            left = pos + 1;
        }
        pos = partition(mass, left, right, cmp);
    } while (pos != k);
}

int main() {
    int n, k;
    std::cin >> n;
    std::cin >> k;
    int * mass = new int[n];
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
        std::cin >> mass[i];

    find_k_static(mass, n, k, cmp());

    std::cout << mass[k];

    delete[] mass;
    return 0;
}