#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string LettersLearnedToday(string word) {
    string result;
    for (const auto& ch : word) {
        if (count(result.begin(), result.end(), ch) == 0) {
            result += ch;
        }
    }
    return result;
}


int AvoidJailDueToTaxFraud(vector<vector<int>> report) {
    vector<int> result;
    for (size_t i = 0; i < report.size(); ++i) {
        for (size_t j = 0; j < report[i].size(); ++j) {
            if (count(result.begin(), result.end(), report[i][j]) != 0) {
                return report[i][j];
            } else {
                result.push_back(report[i][j]);
            }
        }
    }
    return -1;
    }

// Tests
void TestLettersLearnedToday() {
    string word("FFFAAAAA;SSS,HDFFFFFUUU{S{S<KBF"s);
    assert(LettersLearnedToday(word) == "FA;S,HDU{<KB"s);
    word.clear();
    word = string("AAAAAAAA");
    assert(LettersLearnedToday(word) == "A"s);
}

void TestAvoidJailDueToTaxFraud() {
    vector<vector<int>> report{
        {12391203, 3828382, 334934939},
        {45345345, 5341312, 55345345},
        {334934939, 1234122, 657657}
    };
    assert(AvoidJailDueToTaxFraud(report) == 334934939);
    report.clear();
    report = {
        {1, 2, 3},
        {4, 5, 6}
    };
    assert(AvoidJailDueToTaxFraud(report) == -1);
}

void Test() {
    TestLettersLearnedToday();
    TestAvoidJailDueToTaxFraud();
}
int main() {
    Test();
}