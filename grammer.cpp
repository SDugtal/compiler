#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

bool check_string(unordered_map<char, vector<string>>& grammar, int& pos, string str, char LHS) {
    for (const auto& production : grammar[LHS]) {
        int original_pos = pos; 
        bool valid = true; 

        for (char symbol : production) {
            if (symbol >= 'A' && symbol <= 'Z') {
                if (check_string(grammar, pos, str, symbol)) {
                } else {
                    valid = false; 
                    break;
                }
            } else if (symbol == str[pos]) {
                pos++; 
            } else {
                valid = false; 
                break;
            }
        }

        if (valid && pos == str.size()) {
            return true; 
        }

        pos = original_pos; 
    }
    return false; 
}

int main() {
    unordered_map<char, vector<string>> grammar;
    int num;
    char beg_LHS;

    cout << "Welcome to the Grammar Checker!\n";
    cout << "How many grammar rules do you want to define? ";
    cin >> num;

    for (int i = 0; i < num; i++) {
        char LHS;
        int n;

        cout << "Enter the Non-terminal (LHS) for grammar rule " << (i + 1) << ": ";
        cin >> LHS;
        if (i == 0) beg_LHS = LHS;

        cout << "How many productions does " << LHS << " have? ";
        cin >> n;

        cout << "Enter the productions for " << LHS << " (separate each production with a space): ";
        for (int j = 0; j < n; j++) {
            string str;
            cin >> str;
            grammar[LHS].push_back(str);
        }
    }

    string str;
    cout << "Now, please enter the string you want to check: ";
    cin >> str;

    int pos = 0; 
    bool ans = check_string(grammar, pos, str, beg_LHS);
    str = (ans) ? "The string is valid according to the grammar." : "The string is invalid according to the grammar.";
    cout << str << endl;

    return 0;
}
