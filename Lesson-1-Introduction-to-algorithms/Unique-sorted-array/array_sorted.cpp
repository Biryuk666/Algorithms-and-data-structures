#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <sstream>
#include "printer.h"
#include <vector>

// Task #1
void GroupeAndPrint (vector<double> phone_numbers) {
    vector<double> unique_numbers;
    for (auto number : phone_numbers) {
        if (count(unique_numbers.begin(), unique_numbers.end(), number) == 0) {
            int applications_count = static_cast<int>(count(phone_numbers.begin(), phone_numbers.end(), number));
            unique_numbers.push_back(number);
            PrintPhoneInfo(number, applications_count);
        }
    }
}

// Task #2
struct Cryptocurrency {
    string name;
    int count = 0;
    double sum = 0;
};

void AddCryptocurrency(const string& text, vector<Cryptocurrency>& cryptocurrencies) {
    auto separator_pos = text.find(':');
    string name = text.substr(0, separator_pos);
    double sum = stoi(text.substr(separator_pos + 1, text.size()));
    auto it = find_if(cryptocurrencies.begin(), cryptocurrencies.end(), [&name](const auto& i) {
        return i.name == name;
    });
    if (it == cryptocurrencies.end()) {
        Cryptocurrency cryptocurrency;
        cryptocurrency.name = name;
        ++cryptocurrency.count;
        cryptocurrency.sum += sum;
        cryptocurrencies.push_back(cryptocurrency);
    } else {
        ++it->count;
        it->sum += sum;
    }
}

void CryptoCurrencyAnalysis(string file_contents) {
    vector<Cryptocurrency> cryptocurrencies;
    for (auto space_pos = file_contents.find(' '); space_pos != file_contents.npos; space_pos = file_contents.find(' ')) {
        auto text = file_contents.substr(0, space_pos);
        AddCryptocurrency(text, cryptocurrencies);
        file_contents = file_contents.substr(space_pos + 1);      
    }

    AddCryptocurrency(file_contents, cryptocurrencies);

    for (const auto& cryptocurrency : cryptocurrencies) {
        PrintCurrencyInfo(cryptocurrency.name, cryptocurrency.sum/cryptocurrency.count);
    }
}    

//Tests
void TestGroupAndPrint() {
    vector<double> phone_numbers1{
        79000000000,
        79000000000,
        79000000000
    };
    GroupeAndPrint(phone_numbers1);
    vector<double> phone_numbers2{
        79000000000,
        79000000000,
        79000000001,
        79000000002,
        79000000002,
        79000000003,
        79000000003,
        79000000003,
        79000000003,
        79000000004
    };
    GroupeAndPrint(phone_numbers2);

    /*ostringstream output1;
    output1 << GroupeAndPrint(phone_numbers1);
    assert(output.str() == "+79000000000 - applications have been received: 3");
    ostringstream output2;
    output2 << GroupeAndPrint(phone_numbers2);
    assert(output.str() == "+79000000000 - applications have been received: 2\n
                            +79000000001 - applications have been received: 1\n
                            +79000000002 - applications have been received: 2\n
                            +79000000003 - applications have been received: 4\n
                            +79000000004 - applications have been received: 1\n"
    );*/

    cout << __FUNCTION__ << " DONE"s << endl;
}

void TestCryptoCurrencyAnalysis() {
    
    string file_contents1("BTC:600 BTC:600 BTC:600 BTC:600 BTC:600 BTC:600 BTC:600"s);
    CryptoCurrencyAnalysis(file_contents1);
    string file_contents2("BTC:42 BTC:600 BTC:900 DOGE:123456 DOGE:69420 ETH:220 ETH:666 XMR:14 XMR:88"s);
    CryptoCurrencyAnalysis(file_contents2);
    /*ostringstream output1;
    output1 << CryptoCurrencyAnalysis(file_contents1);
    assert(output1.str() == "(\"BTC\", 600)\n");
    ostringstream output2;
    output1 << CryptoCurrencyAnalysis(file_contents2);
    assert(output2.str() == "(\"BTC\", 514.0)\n
                             (\"DOGE\", 96438)\n
                             (\"ETH\", 443)\n
                             (\"XMR\", 51)\n
    )";*/

    cout << __FUNCTION__ << " DONE"s << endl; 
}

void Tests(){
TestGroupAndPrint();
TestCryptoCurrencyAnalysis();

cout << "ALL TESTS DONE" << endl;
}

int main (){
    Tests();
}