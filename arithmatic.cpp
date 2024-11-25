#include <iostream>
#include <stack>
#include <cctype>

using namespace std;

bool isValid(string& exp) {
    stack<char> st;
    bool lastWasOperand = false;
    bool lastWasOperator = false;

    for (char ch : exp) {
        if (isspace(ch)) continue;

        if (isalnum(ch)) {
            lastWasOperand = true;
            lastWasOperator = false;
        }

        else if (ch == '(') {
            st.push(ch);
            lastWasOperand = false;
            lastWasOperator = false;
        }

        else if (ch == ')') {
            if (st.empty() || st.top() != '(') return false;
            st.pop();
            lastWasOperand = true;
            lastWasOperator = false;
        }

        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            if (lastWasOperator) return false;
            lastWasOperand = false;
            lastWasOperator = true;
        }

        else return false;
    }

    return st.empty() && lastWasOperand;
}

int main() {
    string exp;
    string hardCoded = "1+2*(2+2-2/12)*4";

    cout << "Haded coded exp: " << hardCoded << endl;
    cout << "Result: " << (isValid(hardCoded) ? "Valid" : "Invalid") << endl;
    

    cout << "Enter Arithemetic operations: ";
    getline(cin, exp);

    cout << "Result: " << (isValid(exp) ? "Valid" : "Invalid") << endl;

    return 0;
}
