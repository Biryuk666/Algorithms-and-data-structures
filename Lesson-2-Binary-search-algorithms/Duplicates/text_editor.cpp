#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class TextEditor {
    public:

        TextEditor() = default;

        void InsertCharacterAt(int position, char ch) {
            ++text_lenght;
            for (int i = text.size() - 1; i > position; --i) {
                text[i] = text[i - 1];
            }
            text[position] = ch;            
        }

        void BackSpace(int position) {
            for (int i = position + 1; i < text_lenght; ++i) {
                text[i - 1] = text[i];
            }
            --text_lenght;
        }

        int text_lenght = 0;
        vector<char> text = vector<char>(255, ' ');
};

// Tests
void TestTextEditorConstructor() {
    TextEditor editor;
    assert(editor.text_lenght == 0);
    assert(editor.text.size() == 255);
    assert(editor.text[17] == ' ');

    cout << __FUNCTION__ << " DONE"s << endl;
}
void TestInsertCharacterAt() {
    TextEditor editor;
    string text {"Helloworld!"};
    for (size_t i = 0; i < text.size(); ++i) {
        editor.text[i] = text[i];
        ++editor.text_lenght;
    }
    editor.InsertCharacterAt(5, ' ');
    ostringstream out;
    for (int i = 0; i < editor.text_lenght; ++i) {
        out << editor.text[i];
    }
    assert(out.str() == "Hello world!");

    cout << __FUNCTION__ << " DONE"s << endl;
}
void TestBackSpace() {
    TextEditor editor;
    string text {"Hellow world!"};
    for (size_t i = 0; i < text.size(); ++i) {
        editor.text[i] = text[i];
        ++editor.text_lenght;
    }
    editor.BackSpace(5);
    ostringstream out;
    for (int i = 0; i < editor.text_lenght; ++i) {
        out << editor.text[i];
    }
    assert(out.str() == "Hello world!");

    cout << __FUNCTION__ << " DONE"s << endl;
}

void Tests() {
    TestTextEditorConstructor();
    TestInsertCharacterAt();
    TestBackSpace();
}

int main() {
    Tests();
}