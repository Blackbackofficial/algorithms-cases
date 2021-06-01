// Написать алгоритм для решения игры в “пятнашки”. Решением задачи является приведение к виду:
// [ 1 2 3 4 ] [ 5 6 7 8 ] [ 9 10 11 12] [ 13 14 15 0 ], где 0 задает пустую ячейку.
// Достаточно найти хотя бы какое-то решение. Число перемещений костяшек не обязано быть минимальным.

#include <iostream>
#include <array>
#include <cassert>
#include <unordered_map>
#include <queue>

using namespace std;

#define SIZE_FIELD 16
const array<char, SIZE_FIELD>
    FinishField = {
    1, 2, 3, 4,
    5, 6, 7, 8,
    9, 10, 11, 12,
    13, 14, 15, 0
};

class Fifteen {
public:
    array<char, SIZE_FIELD> field{};
    char emptyPos = -1;
    explicit Fifteen(const array<char, SIZE_FIELD>& _field);

    bool can_left() const;
    bool can_right() const;
    bool can_up() const;
    bool can_down() const;

    Fifteen left() const;
    Fifteen right() const;
    Fifteen up() const;
    Fifteen down() const;

    bool operator==(const Fifteen& state) const;
    bool operator<(const Fifteen& state) const;

    Fifteen& operator=(const Fifteen& state) = default;

    bool isValid() const;
    int heuristic() const;

    friend struct StateHash;
};

struct StateHash {
    int operator() (const Fifteen& state) const {
        int hash = 0;
        for (int i : state.field)
            hash = (hash * 31 + i);
        return hash;
    }
};

Fifteen::Fifteen(const array<char, SIZE_FIELD> &_field) {
    field = _field;
    for(int i = 0; i < SIZE_FIELD; i++)
        if( field[i] == 0 )
            emptyPos = (char) i;
    assert( emptyPos != -1 );
}

bool Fifteen::isValid() const {
    int inv = 0;
    for (int i = 0; i < SIZE_FIELD; ++i) {
        if (field[i]) {
            for (int j = 0; j < i; ++j) {
                if (field[j] > field[i]) {
                    ++inv;
                }
            }
        }
    }

    inv += 1 + emptyPos / 4;
    return (inv % 2 == 0);
}

int Fifteen::heuristic() const {
    int h = 0;
    int fullDist;
    for (int i = 0; i < field.size(); ++i) {
        fullDist = (field[i] != 0) ? abs(field[i] - 1 - i) : SIZE_FIELD - i;
        h += fullDist / 4;
        fullDist %= 4;
        h += (fullDist == 3) ? 2 : fullDist;
    }
    return h;
}

bool Fifteen::can_left() const {
    return emptyPos % 4 != 3;
}
bool Fifteen::can_right() const {
    return emptyPos % 4 != 0;
}
bool Fifteen::can_up() const {
    return emptyPos < 12;
}
bool Fifteen::can_down() const {
    return emptyPos > 4;
}
Fifteen Fifteen::left() const {
    assert(can_left());

    Fifteen leftState(*this);
    swap(leftState.field[emptyPos], leftState.field[emptyPos + 1]);
    leftState.emptyPos++;
    return leftState;
}
Fifteen Fifteen::right() const {
    assert(can_right());

    Fifteen rightState(*this);
    swap(rightState.field[emptyPos], rightState.field[emptyPos - 1]);
    rightState.emptyPos--;
    return rightState;
}
Fifteen Fifteen::up() const {
    assert(can_up());

    Fifteen upState(*this);
    swap(upState.field[emptyPos], upState.field[emptyPos + 4]);
    upState.emptyPos += 4;
    return upState;
}
Fifteen Fifteen::down() const {
    assert(can_down());

    Fifteen downState(*this);
    swap(downState.field[emptyPos], downState.field[emptyPos - 4]);
    downState.emptyPos -= 4;
    return downState;
}
bool Fifteen::operator==(const Fifteen &state) const {
    return field == state.field;
}
bool Fifteen::operator<(const Fifteen &state) const {
    return heuristic() > state.heuristic();
}

void Displacement(const array<char, SIZE_FIELD>& field, string* displacement) {
    unordered_map<Fifteen, string, StateHash> viewed;
    Fifteen start(field);

    priority_queue<Fifteen> q;
    q.push(start);
    viewed[start];
    Fifteen finish(FinishField);

    while (!(q.top() == finish)) {
        Fifteen current = q.top();
        q.pop();

        if(current.can_left()) {
            Fifteen leftState = current.left();
            if(viewed.find(leftState) == viewed.end()) {
                q.push(leftState);
                viewed[leftState] = viewed[current] + "L";
            }
        }
        if(current.can_right()) {
            Fifteen rightState = current.right();
            if(viewed.find(rightState) == viewed.end()) {
                q.push(rightState);
                viewed[rightState] = viewed[current] + "R";
            }
        }
        if(current.can_up()) {
            Fifteen upState = current.up();
            if(viewed.find(upState) == viewed.end()) {
                q.push(upState);
                viewed[upState] = viewed[current] + "U";
            }
        }
        if(current.can_down()) {
            Fifteen downState = current.down();
            if(viewed.find(downState) == viewed.end()) {
                q.push(downState);
                viewed[downState] = viewed[current] + "D";
            }
        }
    }
    *displacement = viewed[finish];
}

int main() {
    array<char, SIZE_FIELD> field{};
    string displacement;
    int position;
    for (int i = 0; i < SIZE_FIELD; i++) {
        cin >> position;
        field[i] = (char) (position);
    }

    if (!Fifteen(field).isValid()) {
        cout << -1 << endl;
        return 0;
    }

    Displacement(field, &displacement);
    cout << displacement.size() << endl << displacement << endl;
    return 0;
}