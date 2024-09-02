#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

class DynamicArray {
public:
    int size = 8;
    int* values = new int[size];
    int current_index = 0;

    void Add(int value) {
        values[current_index] = value;
        ++current_index;
        if (current_index == size) {
            Resize(size * 2);
        }
    }

    void Resize(int new_size) {
        int* new_values = new int[new_size];
        for (int i = 0; i < new_size; ++i) {
            if (i < current_index) {
                new_values[i] = values[i];                
                continue;
            }
            new_values[i] = 0;
        }
        swap(values, new_values);
        delete[] new_values;
        size = new_size;
    }
};

class VeryDynamicArray : public DynamicArray {
public:

    void DeleteElementAt(int index) {
        if (current_index == 0 || index < 0 || index > current_index) return;
        for (int i = index; i < current_index; ++i) {
            values[i] = values[i + 1];
        }
        --current_index;
        if (current_index != 0 && 100 / (size / (current_index + 1)) <= 25) {
            Resize(size / 2);
        }
    }
};

void TestAdd() {
    VeryDynamicArray array;
    for (int i = 0; i < 3; ++i) {
        array.Add(i);
    }  
    assert(array.values[0] == 0);
    assert(array.values[1] == 1);
    assert(array.values[2] == 2);

    for (int i = 3; i < 10; ++i) {
        array.Add(i);
    }
    assert(array.size == 16);

    cout << __FUNCTION__ << " DONE"s << endl;
 }

void TestResize() {
    VeryDynamicArray array;
    array.Resize(10);
    assert(array.size == 10);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestDeleteElementAt() {
    VeryDynamicArray array;
    for (int i = 0; i <= 6; ++i) {
        array.Add(i);
    }
    array.DeleteElementAt(3);
    assert(array.current_index == 6);
    assert(array.values[3] != 3);
    array.Add(7);
    assert(array.values[7] = 7);
    for (int i = array.current_index; i >= 2; --i) {
        array.DeleteElementAt(i);
    }
    assert(array.size == 4);
    assert(array.current_index == 1);
    for (int i = array.current_index; i >= 0; --i) {
        array.DeleteElementAt(0);
    }
    assert(array.current_index == 0);
    array.Add(0);
    assert(array.values[0] == 0);
    assert(array.current_index == 1);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestAdd();
    TestResize();
    TestDeleteElementAt();
}

int main () {
    Tests();
}