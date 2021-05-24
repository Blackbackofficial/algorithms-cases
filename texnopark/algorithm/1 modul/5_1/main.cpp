#include <iostream>
#include <cassert>
#include <functional>
#include <utility>

using namespace std;
using Visit = pair<int, int>;

template<typename T>
class Array {
public:
    Array() : size_(0), data_(nullptr) {}

    explicit Array(size_t size) : data_(new T[size]), size_(size) {}

    Array(const Array &other) {
        delete[] data_;
        data_ = new T[other.size()];
        size_ = other.size_;
        for (int i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }

    Array &operator=(const Array &other) {
        if (this != &other)
        {
            delete[] data_;
            data_ = new T[other.size()];
            size_ = other.size_;
            for (int i = 0; i < size_; ++i)
                data_[i] = other.data_[i];
        }
        return *this;
    }

    T &operator[](size_t index) {
        assert(index < size_);
        return data_[index];
    }

    T &operator[](size_t index) const {
        assert(index < size_);
        return data_[index];
    }

public:
    void insertRange(size_t start, const Array<T> &toInsert) {
        for (size_t i = 0; i < toInsert.size(); ++i)
        {
            assert(i + start < size_);
            data_[i + start] = toInsert.data_[i];
        }
    }

    size_t size() const {
        return size_;
    }

    ~Array() {
        delete[] data_;
    }

private:
    T *data_;
    size_t size_;
};

template<typename T, class Comparator>
void merge(const Array<T> &src, Array<T> &dest, size_t start1, size_t end1, size_t start2, size_t end2, const Comparator &comp) {
    size_t currentIndex = 0;
    while (start1 != end1 || start2 != end2) {
        if ((start2 == end2) ||
            ((start1 < end1) && (start2 < end2) && comp(src[start1], src[start2])))
            dest[currentIndex++] = src[start1++];
        else
            dest[currentIndex++] = src[start2++];
    }
}

template<typename T, class Comparator=less<T>>
void mergeSort_(Array<T> &src, size_t start, size_t end, const Comparator &comp = Comparator()) {
    if (start + 1 < end) {
        size_t mid = (start + end) / 2;
        mergeSort_(src, start, mid, comp);
        mergeSort_(src, mid, end, comp);
        Array<T> buf(end - start);
        merge(src, buf, start, mid, mid, end, comp);
        size_t currentIndex = 0;
        while (start != end1 || start2 != end2) {
            if ((start2 == end2) ||
                ((start < end1) && (start2 < end2) && comp(src[start], src[start2])))
                buf[currentIndex++] = src[start++];
            else
                buf[currentIndex++] = src[start2++];
        }
        src.insertRange(start, buf);
    }
}

template<typename T, class Comparator=less<T>>
void mergeSort(Array<T> &src, const Comparator &comp = Comparator()) {
    mergeSort_<T, Comparator>(src, 0, src.size(), comp);
}

template<typename T>
ostream &operator<<(ostream &stream, pair<T, T> p) {
    stream << "{" << p.first << ", " << p.second << "}";
    return stream;
}

int main() {
    int res = 0, first = -1, second = -1;
    size_t count;
    cin >> count;
    Array<Visit> customers(count);
    for (size_t i = 0; i < count; ++i)
        cin >> customers[i].first >> customers[i].second;
    mergeSort(customers);
    for (size_t i = 0; i < count; ++i) {
        Visit buf = customers[i];
        if (buf.first > second) {
            first = buf.second - 1;
            second = buf.second;
            res += 2;
        } else if (buf.first == second || (buf.first > first && buf.second > second)) {
            first = second;
            second = buf.second;
            ++res;
        } else if (buf.first > first && buf.first < second) {
            first = buf.second;
            ++res;
        }
    }
    cout << res << endl;
    return 0;
}