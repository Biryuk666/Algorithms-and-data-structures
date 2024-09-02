#include <algorithm>
#include <cassert>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using namespace std;

class KeyValuePair {
public:
    string key, value;

    KeyValuePair(string key_, string value_) : key(key_), value(value_) {}
};

class HashMap {
public:
    int size = 8;
    optional<KeyValuePair>* entries = new optional<KeyValuePair>[size];
    int number_of_elements = 0;

    int HashFunction(const string& key) {
        int result = 0;
        for (char ch : key) {
            result += static_cast<int>(ch);
        }
        return result;
    }

    void Add(const string& key, const string& value) {
        int index = FindGoodIndex(key);
        entries[index] = KeyValuePair{key, value};
        ++number_of_elements;
        if (number_of_elements == size) {
            Resize(size * 2);
        }
    }

    void Resize(int new_size) {
        optional<KeyValuePair>* new_entries = new optional<KeyValuePair>[new_size];
        for (int index = 0; index < size; ++index) {
            if (entries[index] != nullopt) {
                string key = entries[index]->key;
                int new_index = HashFunction(key) % new_size;
                new_entries[new_index] = entries[index];
            }
        }
        swap(entries, new_entries);
        delete[] new_entries;
        size = new_size;
    }

    optional<string> Get(const string& key) {
        int index = FindGoodIndex(key);
        if (index == -1 || entries[index] == nullopt) {
            return nullopt;
        }
        return entries[index]->value;

    }

    int FindGoodIndex(const string& key) {
        int calculated_hash = HashFunction(key);
        int index = calculated_hash % size;
        for (int i = 0; i < size; ++i) {
            int probing_index = (index + i) % size;
            optional<KeyValuePair> entry = entries[probing_index];
            if (entry == nullopt || entry->key == key) {
                return probing_index;
            }
        }
        return -1;
    }
};

class DynamicHashMap : public HashMap {
public:
    // Task #2
    void DeleteKey(const string& key) {
        int index = FindGoodIndex(key);
        if (index == -1 || entries[index] == nullopt) return;
        entries[index] = nullopt;
        --number_of_elements;
        if (100 / (size / number_of_elements) <= 25) {
            Resize(size / 2);
        }
    }    
    
    // Task #3
    vector<string> GetAllKeys() {
        vector<string> result;
        for (int i = 0; i < size; ++i) {
            if (entries[i] != nullopt) {
                result.push_back(entries[i]->key);
            }
        }
        return result;
    }

    vector<string> GetAllValues() {
        vector<string> result;
        for (int i = 0; i < size; ++i) {
            if (entries[i] != nullopt) {
                result.push_back(entries[i]->value);
            }
        }
        return result;
    }
};

// Tests
void TestHashFunction() {
    DynamicHashMap map;
    for (int i = 1; i <= 100; ++i) {
       assert(map.HashFunction("key") == 329);
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestAdd() {
    DynamicHashMap map;
    map.Add("key1"s, "value1"s);
    map.Add("key2"s, "value2"s);
    int index1 = map.HashFunction("key1"s) % map.size;
    int index2 = map.HashFunction("key2"s) % map.size;
    assert(map.entries[index1]->key == "key1"s);
    assert(map.entries[index2]->key == "key2"s);
    for (int i = 3; i < 10; ++i) {
        map.Add("key"s + to_string(i), "value"s + to_string(i));
    }
    assert(map.size == 16);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestResize() {
    DynamicHashMap map;
    map.Resize(10);
    assert(map.size == 10);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestGet() {
    DynamicHashMap map;
    for (int i = 1; i < 5; ++i) {
        map.Add("key"s + to_string(i), "value"s + to_string(i));
    }
    string answer = *map.Get("key1"s);
    assert(*map.Get("key1"s) == "value1"s);
    assert(*map.Get("key3"s) == "value3"s);
    assert(map.Get("key"s) == nullopt);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestFindGoodIndex() {
    DynamicHashMap map;
    assert(map.FindGoodIndex("key") == 1);
    map.Add("key"s, "value"s);
    assert(map.FindGoodIndex("lex"s) == 2);
    DynamicHashMap map2;
    assert(map2.FindGoodIndex("lex"s) == 1);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestDeleteKey() {
    DynamicHashMap map;
    for (int i = 1; i < 16; ++i){
        map.Add("key"s + to_string(i), "value"s + to_string(i));
    }
    int old_index = map.HashFunction("key1"s) % map.size;
    map.DeleteKey("key3");
    assert(map.number_of_elements == 14);
    map.Add("key3"s, "value3"s);
    for (int i = map.number_of_elements; i > 4; --i) {
        map.DeleteKey("key" + to_string(i));
    }
    assert(map.size == 8);
    assert(map.number_of_elements == 4);
    int new_index = map.HashFunction("key1"s) % map.size;
    assert(new_index != old_index);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestGetAllKeys() {
    DynamicHashMap map;
    for (int i = 1; i < 4; ++i){
        map.Add("key"s + to_string(i), "value"s + to_string(i));
    }
    vector<string> result = map.GetAllKeys();
    sort(result.begin(), result.end());
    vector<string>answer{"key1"s, "key2"s, "key3"s};
    assert(result == answer);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestGetAllValues() {
    DynamicHashMap map;
    for (int i = 1; i < 4; ++i){
        map.Add("key"s + to_string(i), "value"s + to_string(i));
    }
    vector<string> result = map.GetAllValues();
    sort(result.begin(), result.end());
    vector<string>answer{"value1"s, "value2"s, "value3"s};
    assert(result == answer);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestHashFunction();
    TestAdd();
    TestResize();
    TestGet();
    TestFindGoodIndex();
    TestDeleteKey();
    TestGetAllKeys();
    TestGetAllValues();
}

main () {
    Tests();
}