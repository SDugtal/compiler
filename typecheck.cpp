#include <iostream>
#include <regex>
#include <string>
using namespace std;

int detectDataType(const string& input) {
    regex int_pat("^[+-]?[0-9]+$");
    regex float_pat("^[+-]?[0-9]*\\.[0-9]+$");
    regex char_pat("^'[^']'$");
    regex string_pat("^\"[^\"]*\"$");

    if (regex_match(input, int_pat)) return 1;
    else if (regex_match(input, float_pat)) return 2;
    else if (regex_match(input, char_pat)) return 3;
    else if (regex_match(input, string_pat)) return 4;
    else return 0;
}

int main() {
    string val, name;
    int utype;
    
    cout << "Please enter the variable's name: ";
    cin >> name;
    cout << "Please enter its value: ";
    cin >> val;
    cout << "Please specify the type as follows:\n";
    cout<<"========================================================================"<<endl;
    cout<<"| 1 for Integer | 2 for Float | 3 for Char | 4 for String | 0 for None |\n";
    cout<<"========================================================================"<<endl;
    cin >> utype;
    
    if (detectDataType(val) == utype) cout << "The data type is correct.";
    else cout << "The data type is incorrect.";
    
    return 0;
}
