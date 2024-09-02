#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <vector>

using namespace std;

class HashMap {
public:
    size_t size = 8;
    optional<size_t>* entries = new optional<size_t>[size];
    size_t number_of_elements = 0;

    size_t HashNumber(size_t number) {
        if (number == 0) return 0;
        size_t result = 1;
        size_t i = 1;
        while (number / i != 0) {
            if (number/ i % 10 != 0) {
            result *= number / i % 10;
            }
            i *= 10;
        }
        return result;
    }

    void Add(size_t number) {
        size_t index = FindGoodIndex(number);
        entries[index] = number;
        ++number_of_elements;
        if (number_of_elements == size) {
            Resize(size * 2);
        }
    }

    void Resize(size_t new_size) {
        optional<size_t>* new_entries = new optional<size_t>[new_size];
        for (size_t index = 0; index < size; ++index) {
            if (entries[index] != nullopt) {
                size_t number = *entries[index];
                size_t new_index = HashNumber(number) % new_size;
                new_entries[new_index] = entries[index];
            }
        }
        swap(entries, new_entries);
        delete[] new_entries;
        size = new_size;
    }

    size_t FindGoodIndex(size_t number) {
        size_t calculated_hash = HashNumber(number);
        size_t index = calculated_hash % size;
        for (size_t i = 0; i < size; ++i) {
            size_t probing_index = (index + i) % size;
            optional<size_t> entry = entries[probing_index];
            if (entry == nullopt || *entry == number) {
                return probing_index;
            }
        }
        return -1;
    }

    vector<size_t> GetAllNumbers() {
        vector<size_t> result;
        for (size_t i = 0; i < size; ++i) {
            if (entries[i] != nullopt) {
                result.push_back(*entries[i]);
            }
        }
        return result;
    }
};

class HashMapsAreFast {
public:
    // Task #1
    vector<size_t> GetUniqueNumbers(vector<size_t> input_array) {
        HashMap map;
        for (size_t number : input_array) {
            map.Add(number);
        }
        return map.GetAllNumbers();
    }

    // Task #2

    bool AreThereTwoNumbers(vector<size_t> numbers, size_t value) {
        HashMap map;
        for (size_t number : numbers) {
            map.Add(number);
        }
        for (size_t i = 0, j = value; i != j; ++i, --j) {
            size_t i_index = map.FindGoodIndex(i);
            size_t j_index = map.FindGoodIndex(j);
            if (map.entries[i_index] != nullopt && map.entries[j_index] != nullopt) {
                return true;
            }
        }
        return false;
    }
};

// Tests
void TestGetUniqueNumber() {
    HashMapsAreFast map;
    vector<size_t> input_array{12, 15, 17, 21, 17, 17, 15};
    vector<size_t> result = map.GetUniqueNumbers(input_array);
    sort(result.begin(), result.end());
    vector<size_t> answer{12, 15, 17, 21};
    assert(result == answer);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestAreThereTwoNumbers() {
    {
        HashMapsAreFast map;
        vector<size_t> numbers{12, 15, 17, 21, 17, 17, 15};
        assert(map.AreThereTwoNumbers(numbers, 33));
    }
    {
        HashMapsAreFast map;
        vector<size_t> numbers{12, 15, 17, 21, 17, 17, 15};
        assert(!map.AreThereTwoNumbers(numbers, 34));
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestGetUniqueNumber();
    TestAreThereTwoNumbers();
}

int main() {
    Tests();
}