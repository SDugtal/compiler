#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
using namespace std;

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void Three_addr_code_generator(const string& expression) {
    int tempVarCount = 1;
    string operators[256];
    string operands[256];
    int opTop = -1, operandTop = -1;

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;

        if (isalnum(expression[i])) {
            size_t j = i;
            string operand;
            while (isalnum(expression[j])) {
                operand += expression[j];
                j++;
            }
            i = j - 1;
            operands[++operandTop] = operand;
        } 
        else if (is_operator(expression[i])) {
            operators[++opTop] = expression[i];
        }
    }

    while (opTop >= 0 && operandTop >= 1) {
        string temp = "t" + to_string(tempVarCount++);
        cout << temp << " = " << operands[operandTop - 1] << " " << operators[opTop] << " " << operands[operandTop] << endl;
        operands[operandTop - 1] = temp;
        opTop--;
        operandTop--;
    }
}

int main(int argc, char** argv) {
 
    cout << "Expression (hardcoded): z = x + y + w" << endl;
    cout << "Three-Address Code:" << endl;
    Three_addr_code_generator("z = x + y + w");
    cout << endl;

   
    string expression;
    cout << "Enter your own expression: ";
    getline(cin, expression);

    cout << "Three-Address Code (user input):" << endl;
    Three_addr_code_generator(expression);
    cout << endl;

    
    if (argc > 1) {
        string file_path = argv[1];
        ifstream file(file_path);
        if (!file) {
            cout << "Error opening file!" << endl;
            return 1;
        }

        string line;
        while (getline(file, line)) {
            cout << "Expression (from file): " << line << endl;
            cout << "Three-Address Code:" << endl;
            Three_addr_code_generator(line);
            cout << endl;
        }

        file.close();
    }

    return 0;
}
