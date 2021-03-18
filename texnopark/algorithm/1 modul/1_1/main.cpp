/*
 * 1_1. Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. Необходимо найти
 * первую пару индексов i0 и j0, i0 ≤ j0, такую что A[i0] + B[j0] = max {A[i] + B[j],
 * где 0 <= i < n, 0 <= j < n, i <= j}. Требования: Время работы - O(n).
 */
#include <iostream>

void max_index_A(const int * mass_A, const int * mass_B, int size_n, int * pair) {
    int sum = mass_A[0] + mass_B[0];
    int max_i = 0;
    for (int k = 0; k <= size_n; k++) {
       if (k == 0)
           max_i = 0;
       if (mass_A[max_i] < mass_A[k])
           max_i = k;
       if (mass_A[max_i] + mass_B[k] > sum) {
           sum = mass_A[max_i] + mass_B[k];
           pair[0] = max_i;
           pair[1] = k;
       }
    }
}

int main() {
    int size_n;
    std::cin >> size_n;
    int * mass_A = new int[size_n], * mass_B = new int[size_n];

    for (int i = 0; i < size_n; i++)
        std::cin >> mass_A[i];
    for (int j = 0; j < size_n; j++)
        std::cin >> mass_B[j];

    int pair[2] = {0};
    max_index_A(mass_A, mass_B, size_n-1, pair);
    std::cout << pair[0] << " " << pair[1];

    delete[] mass_A;
    delete[] mass_B;
    return 0;
}