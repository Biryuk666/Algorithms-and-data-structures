#include <iostream>
#include <cassert>
#include <random>
#include <vector>

using namespace std;

bool IsSorted (vector<int> array) {
    for (size_t i = 0; i < array.size() - 1; ++i) {
        if (array[i] > array[i + 1]) return false;
    }
    return true;
}

void RandomSort(vector<int>& array) {
    mt19937 r_engine;
    uniform_int_distribution<int> uniform_dist(0, array.size() - 1);
    bool is_sorted = false;
    size_t try_count = 0;
    while (!is_sorted) {
        int first_index = uniform_dist(r_engine);
        int second_index = uniform_dist(r_engine);
        if (first_index == second_index) continue;
        int temp = array[first_index];
        array[first_index] = array[second_index];
        array[second_index] = temp;
        is_sorted =  IsSorted(array);
        ++try_count;
    }
    cout << "Try counter: "sv << try_count << endl;
}

//Tests
void TestRandomSort(){
    vector<int> array{0, 8, 3, 5, 1, 9, 2, 4, 6, 7};
    RandomSort(array);
    vector<int> answer{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    assert(array == answer);
}

int main () {
TestRandomSort();
}
