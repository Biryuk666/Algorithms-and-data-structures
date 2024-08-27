#include <cassert>
#include <iostream>
#include <string>

using namespace std;

// Task #1
int HashString(string value) {
    int result = 0;
    for (char ch : value) {
        result += static_cast<int>(ch);
    }
    return result;
}

// Task #2
int HashInt(int value) {
    if (value == 0) return 0;
    int result = 1;
    int i = 1;
    while (value / i != 0) {
        result *= value / i % 10;
        i *= 10;
    }
    return result;
}

// Task #3
class Student {
public:
    Student(int age_, string name_) : age(age_), name(name_) {}

    int age;
    string name;
};

int HashStudent(Student value) {
    return HashString(value.name) + HashInt(value.age);
}

// Tests
void TestHashString() {
    for (int i = 1; i <= 100; ++i) {
        assert(HashString("key") == 'k' + 'e' + 'y');
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestHashInt() {
    for (int i = 1; i <= 100; ++i) {
        assert(HashInt(234) == 24);
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestHashStudent() {
    for (int i = 1; i <= 100; ++i) {
        assert(HashStudent({29, "Vladislav"s}) == 952);
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestHashString();
    TestHashInt();
    TestHashStudent();
}

int main() {
    Tests();
}