#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class UrbanDictionary {
public:
    UrbanDictionary() = default;

    void InsertNewWord(string word) {
        int left = 0;
        int right = static_cast<int>(new_russian_dictionary_.size());
        while (left < right) {
            int middle = (left + right) / 2;
            if (new_russian_dictionary_[middle] < word) {
                left = middle +1;
                continue;
            } else {
                right = middle;
                continue;
            }
        }
        if (word == new_russian_dictionary_[left]) return;
        new_russian_dictionary_.push_back(""s);
        int dict_size = static_cast<int>(new_russian_dictionary_.size());
        for (int i = dict_size - 1; i > left; --i) {
            new_russian_dictionary_[i] = new_russian_dictionary_[i -1];
        }
        new_russian_dictionary_[left] = word;
    }

    vector<string> GetDict() const {
        return new_russian_dictionary_;
    }

private:
    vector<string>new_russian_dictionary_{"Content"s, "Fashion"s, "Fixer"s, "Hipster"s, "Luther"s, "Trend"s}; // ["Контент", "Лутер", "Тренд", "Фиксер", "Фэшн", "Хипстер"]
};

// Tests
void TestInsertNewWord() {
    {
        UrbanDictionary dict;
        vector<string> base_dict{"Content"s, "Fashion"s, "Fixer"s, "Hipster"s, "Luther"s, "Trend"s};
        assert(dict.GetDict() == base_dict); // constructor test;
        dict.InsertNewWord("OMG"s);
        vector<string> answer{"Content"s, "Fashion"s, "Fixer"s, "Hipster"s, "Luther"s, "OMG"s, "Trend"s};
        assert(dict.GetDict() == answer);
    }
    {
        UrbanDictionary dict;
        dict.InsertNewWord("Abuse"s);
        vector<string> answer{"Abuse"s, "Content"s, "Fashion"s, "Fixer"s, "Hipster"s, "Luther"s, "Trend"s};
        assert(dict.GetDict() == answer);
    }
    {
        UrbanDictionary dict;
        dict.InsertNewWord("UWU"s);
        vector<string> answer{"Content"s, "Fashion"s, "Fixer"s, "Hipster"s, "Luther"s, "Trend"s, "UWU"s};
        assert(dict.GetDict() == answer);
    }
    {
        UrbanDictionary dict;
        dict.InsertNewWord("Hipster"s);
        vector<string> answer{"Content"s, "Fashion"s, "Fixer"s, "Hipster"s, "Luther"s, "Trend"s};
        assert(dict.GetDict() == answer);
    }

    cout << __FUNCTION__ << " DONE"s << endl;
}

int main() {
    TestInsertNewWord();
}