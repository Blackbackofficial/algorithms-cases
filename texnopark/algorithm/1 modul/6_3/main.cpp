/*
 * 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
int partition(T * mass, int left, int right)
{
    int pivot = left+ rand() % (right-left);
    if (right - left <= 1)
        return 0;
    std::swap(mass[pivot], mass[right - 1]);
    pivot = mass[right - 1];
    int i = left, j = right - 1;
    while (i <= j) {
        while (mass[i] < pivot)
            i++;
        while (j >= 0 && mass[j] >= pivot)
            j--;
        if (i < j)
            std::swap(mass[i++], mass[j--]);
    }
    std::swap(mass[i], mass[right - 1]);
    return i;
}

template<typename T>
void find_k_static(T * mass, int n, int k) {
    int left = 0, right = n;
    while(left < right) {
        int pos = partition(mass, left, right);
        if (pos > k) {
            right = pos;
        } else if (pos < k) {
            left = pos + 1;
        } else {
            break;
        }
    }
}

int main() {
    int n, k;
    std::cin >> n;
    std::cin >> k;
    int * mass = new int[n];
    srand(time(nullptr));
    for (int i = 0; i < n; i++)
        std::cin >> mass[i];

    find_k_static(mass, n, k);
    std::cout << mass[k];

    delete[] mass;
    return 0;
}

