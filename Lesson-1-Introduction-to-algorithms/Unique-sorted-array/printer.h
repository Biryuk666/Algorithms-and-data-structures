#pragma once
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

void PrintPhoneInfo(double phone_number, int applications_count) {
    cout << "+"s << fixed << setprecision(0) << phone_number << " - applications have been received: "s << applications_count << endl;
}

void PrintCurrencyInfo(string name, double amount) {
    cout << "(\"" << name << "\"" << ", "s << amount << ")"s <<endl;
}

/*def print_phone_info(phone: int, count: int):
    print("+%d — поступило заявок: %d" % (phone, count))


def print_currency_info(name: str, amount: float):
    print("%s: %.3f" % (name, amount))
*/