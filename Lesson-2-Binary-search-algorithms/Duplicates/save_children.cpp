#include <cassert>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

void PermutateWords(vector<string>& words) {
    for (size_t i = 0; i < words.size() - 1; ++i) {
        for (size_t j = 0; j < words.size(); ++j) {
            if (i == j) continue;
            if (words[i] == words[j]) {
                char temp = words[i][0];
                for (size_t k = 0; k < words[i].size() - 1; ++k) {
                    words[i][k] = words[i][k + 1];
                }
                words[i][words[i].size() - 1] = temp;
                i = -1;
            }
        }
    }
}

// Tests
void TestPermutateWords() {
    vector<string> words{"lada", "uaz", "uaz", "uaz", "lada"};
    PermutateWords(words);
    vector<string> answer{"adal", "zua", "azu", "uaz", "lada"};
    assert(words == answer);
}

int main () {
TestPermutateWords();
}
