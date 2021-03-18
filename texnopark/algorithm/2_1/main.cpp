/*
 * 2_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента
 * массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего
 * B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. n, m ≤ 10000. Требования:  Время работы поиска k для
 * каждого элемента B[i]: O(log(k)). Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для
 * бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
 */
#include <iostream>

int exp_search(const int * mass_A, int value_B, int size_A) {
    int index = 0;
    for (int i = 0; size_A >= index && mass_A[index] <= value_B; i++)
        index = 1 << i;

    index = index > size_A ? size_A : index;
    return index;
}

int bin_search(const int * mass_A, int left, int right, int value_B) {
    if (mass_A[right] < value_B)
        return right + 1;
    if (mass_A[left] >= value_B)
        return left;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (mass_A[mid] > value_B) {
            right = mid;
        } else
            left = mid + 1;
    }
    if (right > 1 && mass_A[right - 1] == value_B)
        return right - 1;
    return right;
}

int main() {
    int size_n, size_m;
    std::cin >> size_n;
    std::cin >> size_m;
//    assert(size_n > 0 && size_m > 0 && size_n <= 10000 && size_m <= 10000);
    int * mass_A = new int[size_n];
    int * mass_B = new int[size_m];

    for (int k = 0; k < size_n; k++) {
        std::cin >> mass_A[k];
    }
    for (int i = 0; i < size_m; i++) {
        std::cin >> mass_B[i];
    }

    for (int i = 0; i < size_m; i++) {
        int pos_first = exp_search(mass_A, mass_B[i], size_n-1);
        int final_index  = bin_search(mass_A, pos_first/2, pos_first, mass_B[i]);
        std::cout << final_index << " ";
    }

    delete[] mass_A;
    delete[] mass_B;
    return 0;
}
