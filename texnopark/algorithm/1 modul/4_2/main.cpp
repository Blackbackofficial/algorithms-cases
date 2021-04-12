/*
 * 4_2. Быстрое сложение. Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел
 * равно их сумме. Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений.
 * ((1+2)+3) -> 1+2 + 3+3 = 9
 * ((1+3)+2) -> 1+3 + 4+2 = 10
 * ((2+3)+1) -> 2+3 + 5+1 = 11
 * Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел.
 */

#include <iostream>
#define START 2
struct cmp {
    bool operator()(const int& left, const int& right) {return left < right;}
};

template<class CMP>
class HEAP {
public:
    int heap_size;
    CMP cmp;

    explicit HEAP(int n = 0, CMP comp = CMP()) {
        cmp = comp;
        heap_size = n;
        size_duo = heap_size*2;
        heapMass = nullptr;
    }

    ~HEAP() {
        delete[] heapMass;
    }

    void Insert(int element) {
        if (heapMass == nullptr || heap_size == size_duo)
            newSize();
        heap_size++;
        heapMass[heap_size - 1] = element;
        buildHeap();
    }

    int ExtractMin() {
        if (heap_size == 0 || heapMass == nullptr)
            return 0;
        // Запоминаем значение корня.
        int firstEl = heapMass[0];
        heap_size--;
        // Вызываем SiftDown для корня.
        if(heap_size != 0) {
            std::swap(heapMass[0], heapMass[heap_size]);
            siftDown(0);
        }
        return firstEl;
    }

    void buildHeap() {
        for (int index = (heap_size) / 2 - 1; index >= 0; --index) {
            siftDown(index);
        }
    }

private:
    int * heapMass;
    int size_duo;

    void siftDown(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        // Ищем большего сына, если такой есть.
        int largest = index;
        if (left < heap_size  && cmp(heapMass[left], heapMass[largest]))
            largest = left;
        if (right < heap_size && cmp(heapMass[right], heapMass[largest]))
            largest = right;
        // Если больший сын есть, то проталкиваем корень в него.
        if (largest != index) {
            std::swap(heapMass[index], heapMass[largest]);
            siftDown(largest);
        }
    }

    void newSize() {
        if (heapMass == nullptr) {
            heapMass = new int[START];
            heap_size = 0;
            size_duo = START;
            return;
        }
        size_duo = heap_size << 1;
        int * newMass = new int[size_duo];

        for (int i = 0; i < heap_size; i++)
            newMass[i] = heapMass[i];
        delete[] heapMass;
        heapMass = newMass;
    }
};

template<class CMP>
void summing(HEAP<CMP> * heap, int * computeTime) {
    if (heap == nullptr)
        return;
    if (heap->heap_size == 1)
        *computeTime = heap->ExtractMin();
    else {
        while (heap->heap_size > 1) {
            int last = heap->ExtractMin();
            int prelast = heap->ExtractMin();
            *computeTime += last + prelast;
            heap->Insert(prelast + last);
        }
    }
    if (*computeTime < 0) // у нас натуральное число должно быть
        *computeTime = *computeTime * -1;
}

int main() {
    int n, element;
    std::cin >> n;
    HEAP<cmp> heap;
    for (int i = 0; i < n; i++) {
        std::cin >> element;
        heap.Insert(element);
    }
    int computeTime = 0;
    summing(&heap, &computeTime);
    std::cout << computeTime;
    return 0;
}