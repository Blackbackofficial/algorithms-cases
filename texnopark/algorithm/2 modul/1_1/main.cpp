// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией. Хранимые
// строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована с помощью вычисления
// значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при
// добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4. Структура данных должна поддерживать
// операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
// 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
// g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.

#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#define NOTFOUND -1
#define START 7

struct MyHash {
    size_t operator() (const std::string* str, int m) {
        int hash = 0;
        for (char i : *str)
            hash = (hash * START + i) % m ;
        return hash;
    }
};

template<class Hash>
class HashTable {
public:
    Hash hash;
    std::vector<std::string> structure;
    size_t Msize;
    size_t Rsize;
    explicit HashTable(int size) {
        Rsize = 0;
        Msize = size;
        for (int i = 0; i < Msize; ++i)
            structure.emplace_back("EMPTY");
    };

    bool Insert(std::string value,  size_t volume);

    bool Delete(std::string str);

    int Control(std::string &value, size_t volume);

    HashTable &operator = (HashTable& Nhash) {
        if (this == &Nhash)
            return *this;

        structure = Nhash.structure;
        Msize = Nhash.Msize;
        return *this;
    };
};

template<class Hash>
int HashTable<Hash>::Control(std::string &value, size_t volume) {
    int Nhash = hash(&value, Msize);

    if (structure[Nhash] == value)
        return Nhash;

    volume++;
    int next = (Nhash +  3 * volume + 8 * (int) pow(volume, 2)) % Msize;

    while (structure[next] != "EMPTY") {
        if (next == Nhash)
            return NOTFOUND;
        else if (structure[next] == value)
            return next;

        volume++;
        next = (Nhash +  3 * volume + 8 * (int) pow(volume, 2)) % Msize;
    }
    return NOTFOUND;
}

template<class Hash>
bool HashTable<Hash>::Delete(std::string str) {
    int control = Control(str, 0);

    if(control == NOTFOUND)
        return false;

    structure[control] = "DELETE";
    Rsize--;
    return true;
}

template<class Hash>
bool HashTable<Hash>::Insert(std::string value, size_t volume) {
    int control = Control( value, 0);

    if (control != NOTFOUND)
        return false;

    int Nhash = hash(&value, Msize);
    int next = Nhash;

    while (structure[next] != "DELETE"  && structure[next] != "EMPTY") {
        volume++;
        next = (Nhash +  3 * volume + 8 * (int) pow(volume, 2)) % Msize;
    }

    structure[next] = value;
    Rsize++;

    if (Rsize * 4 == Msize * 3) {
        HashTable<MyHash> Dhash(Msize * 2);

        for (size_t i = 0; i < Msize; i++)
            if (structure[i] != "EMPTY" && structure[i] != "DELETE") {
                bool status = Dhash.Insert(structure[i], 0);
                if (!status)
                    return false;
            }
        *this = Dhash;
    }
    return true;
}



bool parser(char sign, std::string &text, HashTable<MyHash> &hash) {
    if (sign == '+')
        return hash.Insert(text, 0);
    else if (sign == '-')
        return hash.Delete(text);
    else if (sign == '?')
        return hash.Control(text, 0) != NOTFOUND;
    return false;
}

int main() {
    HashTable<MyHash> hash(START + 1);
    char sign;
    std::string text;

    while(std::cin >> sign) {
        getline(std::cin, text);
        parser(sign, text, hash) ? std::cout << "OK" << std::endl : std::cout << "FAIL" << std::endl;
    }

    return 0;
}