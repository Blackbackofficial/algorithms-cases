#include "vector"
#include <algorithm>  // sort
#include <cassert>
#include <cmath>

using namespace std;

vector<int> sort_squares(const vector<int>&);

vector<int> sort_squares(const vector<int>& seq) {
    vector <int> mass = seq;
    for (int i = 0; i < mass.size(); i++) {
        mass[i] = pow(mass[i],2);
    }
    sort(mass.begin(), mass.end());
    return mass;
}

void test() {
    assert((sort_squares({-2, -1, 1, 1, 3}) == vector <int> {1, 1, 1, 4, 9}));
}
int main() {
    test();
    return 0;
}