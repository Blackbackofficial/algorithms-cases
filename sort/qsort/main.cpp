#include <iostream>

using namespace std;

void quicksort(int *mas, int first, int last)
{
    int mid, count;
    int f=first, l=last;
    mid=mas[(f+l) / 2]; //вычисление опорного элемента
    do
    {
        while (mas[f] < mid) f++;
        while (mas[l] > mid) l--;
        if (f <= l) //перестановка элементов
        {
            count=mas[f];
            mas[f]=mas[l];
            mas[l]=count;
            f++;
            l--;
        }
    } while (f < l);
    if (first < l) quicksort(mas, first, l);
    if (f < last) quicksort(mas, f, last);
}

int main() {
    int n=9;
    int A[n];
    int first, last;
    cout<<"Исходный массив: ";
    for (int i=0; i<n; i++)
    {
        A[i]=rand()%100;
        cout<<A[i]<<" ";
    }
    first = 0; last = sizeof(A)/sizeof(A[0]);
    quicksort(&A[0], first, last);
    cout<<endl<<"Результирующий массив: ";
    for (int i=0; i<n; i++) cout<<A[i]<<" ";
    return 0;
}