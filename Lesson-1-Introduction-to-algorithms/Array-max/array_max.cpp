#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// Task #1
int FindSmallestTransaction(vector<int> transactions) {
    bool flag = true;
    int min_transaction = 0;
    for (auto value : transactions) {
        if (value < 0) {
            min_transaction = max((flag ? value : min_transaction), value);
        }
        flag = false;
    }
    return min_transaction;
}

// Task #2
int FindBestStudentMistakes(vector<int> results) {
    bool flag = true;
    int min_mistakes_value = 0;
    for (auto value : results) {
        if (value >= 0) {
            min_mistakes_value = min((flag ? value : min_mistakes_value), value);
        }
        flag = false;
    }
    return min_mistakes_value;
}
// Task #3
float FindAverageTime(vector<int> statistic) {
    int total_time = accumulate(statistic.begin(), statistic.end(), 0);
    float average_time = (float)total_time / statistic.size();
    return average_time;    
}
    
// Task #4
int FindMostProfitableClient(vector<vector<int>> income) {
    int more_profitable_client_index = 0;
    int more_profitable_client_income = 0;
    for (size_t i = 0; i < income.size(); ++i) {
        int payments_amount = accumulate(income[i].begin(), income[i].end(), 0);
        if (more_profitable_client_income < payments_amount) {
            more_profitable_client_index = i;
            more_profitable_client_income = payments_amount;
        }
    }
    return more_profitable_client_index;
}

// Tests
void TestFindSmallestTransaction() {
    vector<int> transactions{-1392, -1920, -7, -453, -91234};
    assert(FindSmallestTransaction(transactions) == -7);
    transactions.push_back(0);
    assert(FindSmallestTransaction(transactions) == -7);
    transactions.push_back(500);
    assert(FindSmallestTransaction(transactions) == -7);
    transactions.push_back(-1);
    assert(FindSmallestTransaction(transactions) == -1);

    cout << __FUNCTION__ << " DONE"s << endl;
}
void TestFindBestStudentMistakes() {
    vector<int> result{9, 4, 1, 8, 7, 13, 6, 5};
    assert(FindBestStudentMistakes(result) == 1);
    result.push_back(-10);
    assert(FindBestStudentMistakes(result) == 1);
    result.push_back(0);
    assert(FindBestStudentMistakes(result) == 0);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestFindAverageTime() {
    vector<int> statistic{9, 4,1, 8, 7, 9, 4, 1, 8, 7, 8, 7, 18, 3, 13, 6, 5};
    float answer = (float)accumulate(statistic.begin(), statistic.end(), 0) / statistic.size();
    assert(FindAverageTime(statistic) == answer);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestFindMostProfitableClient() {
    vector<vector<int>> income{
        {95, 67, 13, 55, 44, 11, 10},
        {7,190, 4, 44, 11, 1, 99},
        {0, 5, -1, 500, 14, 90, 1}
    };
    assert(FindMostProfitableClient(income) == 2);
    income.push_back({0,0,0,1,100,10});
    assert(FindMostProfitableClient(income) == 2);
    income.push_back({100,100,100,100,100,1000});
    assert(FindMostProfitableClient(income) == 4);

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Test() {
    TestFindSmallestTransaction();
    TestFindBestStudentMistakes();
    TestFindAverageTime();
    TestFindMostProfitableClient();
    cout << "ALL TESTS DONE"s << endl;
}

int main() {
    Test();
}