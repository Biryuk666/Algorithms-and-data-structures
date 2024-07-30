#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Task #1
bool DoIKnowThisLanguage(const vector<string>& languages, const string& search) {
    int left = 0;
    int right = languages.size() - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (languages[middle] < search) {
            left = middle + 1;
        } else if (languages[middle] > search) {
            right = middle - 1;
        } else {
            return true;
        }
    }
    return false;
}

// Task #2
class DatingUser {
public:
    int iq = 0;
    string name;

    DatingUser(int iq_, string name_) : iq(iq_), name(name_) {}
};

bool FindBound(const vector<DatingUser>& list, int& search, int& bound_index) {
    int left = 0;
    int right = list.size() - 1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (list[middle].iq < search) {
            left = middle + 1;
        } else if (list[middle].iq > search) {
            right = middle - 1;
        } else {
            bound_index = middle;
            return true;
        }
    }
    return false;
}

vector<DatingUser> FindUsersByIQ(const vector<DatingUser>& users_sorted_by_iq, int lower_iq_bound, int professor_iq) {
    if (users_sorted_by_iq.empty()) throw invalid_argument("List is empty"s);
    if (professor_iq < lower_iq_bound || lower_iq_bound > users_sorted_by_iq.back().iq || professor_iq < users_sorted_by_iq[0].iq) throw invalid_argument("Invalid arguments"s);

    int lower_bound_index = INT_MIN;
    bool is_finded = false;
    while (!is_finded || lower_iq_bound <= professor_iq) {
        is_finded = FindBound(users_sorted_by_iq, lower_iq_bound, lower_bound_index);
        if (is_finded) break;
        ++lower_iq_bound;
    }

    for (int i = lower_bound_index; users_sorted_by_iq[i].iq == users_sorted_by_iq[lower_bound_index].iq && i > 0; --i) {
        lower_bound_index = i;
    }

    int upper_bound_index = INT_MIN;
    is_finded = false;
    while (!is_finded || lower_iq_bound >= professor_iq) {
        is_finded = FindBound(users_sorted_by_iq, professor_iq, upper_bound_index);
        if (is_finded) break;
        --professor_iq;
    }

    for (int i = upper_bound_index;users_sorted_by_iq[i].iq == users_sorted_by_iq[upper_bound_index].iq && i > 0; ++i) {
        upper_bound_index = i;
    }
    
    if (lower_bound_index == INT_MIN || upper_bound_index == INT_MIN) return {};
    return {users_sorted_by_iq.begin() + static_cast<long long>(lower_bound_index), users_sorted_by_iq.begin() + static_cast<long long>(upper_bound_index) + 1};
}

// Task #3
size_t FindPhoneNumber(const vector<size_t>& sorted_phone_numbers, size_t query) {
    int left = 0;
    int right = sorted_phone_numbers.size() - 1;
    if (sorted_phone_numbers[0] < sorted_phone_numbers[1]) {
        while (left <= right) {
            int middle = (left + right) / 2;
            if (sorted_phone_numbers[middle] < query) {
                left = middle + 1;
            } else if (sorted_phone_numbers[middle] > query) {
                right = middle - 1;
            } else {
                return sorted_phone_numbers[middle];
            }
        }
        return 0;
    }
    while (left <= right) {
        int middle = (left + right) / 2;
        if (sorted_phone_numbers[middle] > query) {
            left = middle + 1;
        } else if (sorted_phone_numbers[middle] < query) {
            right = middle - 1;
        } else {
            return sorted_phone_numbers[middle];
        }
    }
    return 0;
}

// Tests
void TestDoIKnowThisLanguage() {
    vector<string> list{"ADA", "ALGOL", "B", "BASIC", "C", "C++"};
    assert(DoIKnowThisLanguage(list, "ADA"));
    assert(DoIKnowThisLanguage(list, "BASIC"));
    assert(DoIKnowThisLanguage(list, "C++"));
    assert(!DoIKnowThisLanguage(list, "A"));
    assert(!DoIKnowThisLanguage(list, "C#"));
    assert(!DoIKnowThisLanguage(list, "JAVASCRIPT"));

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestFindUsersByIQ() {
    vector<DatingUser> list{{50, "Victoria"s}, {52, "Maria"s}, {52, "Evgeniya"s}, {52, "Svetlana"s}, {70, "Marina"s}, {77, "Lyudmila"s}, {80, "Diana"s}, {80, "Natasha"s}, {90, "Kseniya"s}};
    {
        vector<DatingUser> result = FindUsersByIQ(list, 51, 81);
        assert(result[0].name == "Maria"s);
        assert(result.back().name == "Natasha"s);
    }
    {
        vector<DatingUser> result = FindUsersByIQ(list, 50, 90);
        assert(result[0].name == "Victoria"s);
        assert(result.back().name == "Kseniya"s);
    }
    {
        vector<DatingUser> result = FindUsersByIQ(list, 45, 100);
        assert(result[0].name == "Victoria"s);
        assert(result.back().name == "Kseniya"s);
    }
    {
        vector<DatingUser> result = FindUsersByIQ(list, 52, 52);
        assert(result[0].name == "Maria"s);
        assert(result.back().name == "Svetlana"s);
    }
    {
        vector<DatingUser> result = FindUsersByIQ(list, 55, 65);
        assert(result.empty());
    }
    {
        try {
        vector<DatingUser> result = FindUsersByIQ(list, 100, 105);
        } catch (...) {}
    }
    {
        try {
        vector<DatingUser> result = FindUsersByIQ(list, 40, 45);
        } catch (...) {}
    }
    {
        try {
        vector<DatingUser> result = FindUsersByIQ(list, 55, 50);
        } catch (...) {}
    }
    {
        list.clear();
        try {
        vector<DatingUser> result = FindUsersByIQ(list, 50, 90);
        } catch (...) {}
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestFindPhoneNumber() {
    vector<size_t> list1{79000000000, 79000000001, 79000000002, 79000000004, 79000000005, 79000000006};
    vector<size_t> list2{79000000006, 79000000005, 79000000004, 79000000002, 79000000001, 79000000000};
    assert(FindPhoneNumber(list1, 79000000002) == 79000000002);
    assert(FindPhoneNumber(list2, 79000000002) == 79000000002);
    assert(FindPhoneNumber(list1, 78999999999) == 0);
    assert(FindPhoneNumber(list1, 79000000003) == 0);
    assert(FindPhoneNumber(list1, 79000000007) == 0);
    assert(FindPhoneNumber(list2, 78999999999) == 0);
    assert(FindPhoneNumber(list2, 79000000003) == 0);
    assert(FindPhoneNumber(list2, 79000000007) == 0);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestDoIKnowThisLanguage();
    TestFindUsersByIQ();
    TestFindPhoneNumber();
}

int main () {
    Tests();
}