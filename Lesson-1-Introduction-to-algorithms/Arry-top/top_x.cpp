#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

int FindMaxUnderBoundary(const vector<int>& list, int top_boundary) {
    int current_max = INT_MIN;

    for (size_t i =0; i < list.size(); ++i) {
        if (list[i] <= top_boundary) {
            current_max = max(current_max, list[i]);
        }
    }    
    if (current_max == INT_MIN) {
        throw "top boundary less than the values of the vector's elements"s; 
    }
    return current_max;
}

int FindMinUnderBoundary(const vector<int>& list, int bottom_boundary) {
    int current_min = INT_MAX;

    for (auto value : list) {
        if (value >= bottom_boundary) {
            current_min = min(current_min, value);
        }
    }
    if (current_min == INT_MAX) {
        throw "bottom boundary more than the values of the vector's elements"s; 
    }
    return current_min;
}

vector<int> FindTopElements(vector<int>& list, int number_of_elements) {
    if (number_of_elements > list.size()) {
        throw "number of element more than list size"s;
    }
    vector<int> top_elements(number_of_elements);
    int previous_max = INT_MAX;
    int index = 0;
    while(number_of_elements != 0) {
        int current_max = FindMaxUnderBoundary(list, previous_max);
        previous_max = current_max;
        top_elements[index++] = current_max;
        auto it = find(list.begin(), list.end(), current_max);
        list.erase(it);
        --number_of_elements;
    }

    return top_elements;
}

vector<int> FindBottomElements(vector<int>& list, int number_of_elements) {
    if (number_of_elements > list.size()) {
        throw "number of element more than list size"s;
    }
    vector<int> bottom_elements(number_of_elements);
    int previous_min = INT_MIN;
    int index = 0;
    while(number_of_elements != 0) {
        int current_min = FindMinUnderBoundary(list, previous_min);
        previous_min = current_min;
        bottom_elements[index++] = current_min;;
        auto it = find(list.begin(), list.end(), current_min);
        list.erase(it);
        --number_of_elements;
    }

    return bottom_elements;
}

//Tests
void TestFindMaxUnderBoundary() {
    try {
        vector<int> list{10, 20, 30, 40};
        FindMaxUnderBoundary(list, -1);
    } 
    catch (const string& error_message) {
        assert(!error_message.empty());
    }
}

void TestFindBottomElements() {
    vector<int> list{40, 50, 60, 10, 20, 30, 70, 80};
    vector<int> answer{10, 20, 30};
    assert(FindBottomElements(list, 3) == answer);
}


void TestFindTopElements() {
    vector<int> list{100, 100, 100, 55, 8};
    vector<int> answer{100, 100, 100};
    assert(FindTopElements(list, 3) == answer);
}


void Test() {
    TestFindMaxUnderBoundary();
    TestFindBottomElements();
    TestFindTopElements();
}

int main() {
    Test();
}
