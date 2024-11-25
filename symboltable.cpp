#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <iomanip>  // For formatting the table

using namespace std;

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    UNKNOWN
};

struct SymbolEntry {
    string name;
    string type;
    string value;
    int scopeLevel;
};

class SymbolTable {
private:
    unordered_map<string, SymbolEntry> table;

public:
    void insert(const string& name, const string& type, const string& value, int scopeLevel) {
        SymbolEntry entry = {name, type, value, scopeLevel};
        table[name] = entry;
    }

    SymbolEntry* lookup(const string& name) {
        if (table.find(name) != table.end()) {
            return &table[name];
        }
        return nullptr;
    }

    void display() {
        cout << left << setw(10) << " | Name |" << setw(10) << " | Type | " << setw(10) << " | Value | " << setw(10) << " | Scope |\n";
        cout << "---------------------------------------------\n";
        
        for (const auto& entry : table) {
            cout << left << setw(10) << "|" << entry.second.name << "|"
                 << setw(10) << "|" <<  entry.second.type
                 << "|" <<  setw(10) << entry.second.value 
                 << setw(10) << entry.second.scopeLevel << endl; 
        }
    }
};

class Lexer {
private:
    vector<string> keywords = {"int", "float", "return", "if", "else", "while"};

public:
    bool isKeyword(const string& token) {
        for (const string& keyword : keywords) {
            if (token == keyword) return true;
        }
        return false;
    }

    void tokenizeAndPopulateSymbolTable(const string& code, SymbolTable& symTable) {
        string token, lastType;
        int scopeLevel = 0;

        for (size_t i = 0; i < code.length(); ++i) {
            char c = code[i];
            if (isspace(c)) continue;

            if (isalpha(c)) {
                token.clear();
                while (i < code.length() && (isalnum(code[i]) || code[i] == '_')) {
                    token += code[i++];
                }
                --i;

                if (isKeyword(token)) {
                    lastType = token;
                } else if (!lastType.empty()) {
                    symTable.insert(token, lastType, "", scopeLevel);
                    lastType.clear();
                }
            } else if (isdigit(c)) {
                token.clear();
                while (i < code.length() && isdigit(code[i])) {
                    token += code[i++];
                }
                --i;
                symTable.insert("constant_" + token, "int", token, scopeLevel);
            } else if (c == '{') {
                scopeLevel++;
            } else if (c == '}') {
                scopeLevel--;
            }
        }
    }
};

int main() {
    SymbolTable symTable;
    Lexer lexer;

    string userInput;
    cout << "Enter your code: ";
    getline(cin, userInput);

    lexer.tokenizeAndPopulateSymbolTable(userInput, symTable);
    symTable.display();

    return 0;
}