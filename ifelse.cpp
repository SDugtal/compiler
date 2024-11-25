#include <iostream>
#include <string>
using namespace std;

int convertStringToInt(const string& str) {
    int result = 0;
    for (char c : str) {
        result = result * 10 + (c - '0');
    }
    return result;
}

void evaluateCondition(const string& input) {
    if (input.size() < 5 || input.substr(0, 3) != "if(" || input.back() != ')') {
        cout << "Error: Input should start with 'if(' and end with ')'" << endl;
        return;
    }

    string condition = input.substr(3, input.size() - 4);

    size_t pos = string::npos;
    char operation = '\0';
    
    if ((pos = condition.find("==")) != string::npos) {
        operation = '=';
    } else if ((pos = condition.find('>')) != string::npos) {
        operation = '>';
    } else if ((pos = condition.find('<')) != string::npos) {
        operation = '<';
    } else {
        cout << "Error: No valid comparison operator found (==, >, <)" << endl;
        return;
    }

    string leftOperand = condition.substr(0, pos);
    string rightOperand = condition.substr(pos + (operation == '=' ? 2 : 1));

    int leftValue = convertStringToInt(leftOperand);
    int rightValue = convertStringToInt(rightOperand);
    bool isConditionTrue = false;

    if (operation == '=') {
        isConditionTrue = (leftValue == rightValue);
    } else if (operation == '>') {
        isConditionTrue = (leftValue > rightValue);
    } else if (operation == '<') {
        isConditionTrue = (leftValue < rightValue);
    }

    if (isConditionTrue) {
        cout << "Condition is TRUE" << endl;
    } else {
        cout << "Condition is FALSE" << endl;
    }
}

int main(int argc, char** argv) {
    string inputCondition = (argc > 1) ? argv[1] : "if(100>99)";
    evaluateCondition(inputCondition);
    return 0;
}