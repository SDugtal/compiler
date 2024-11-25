#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <cctype>
using namespace std;

enum class TokenType {
    ILLEGAL, END, IDENT, INT, ASSIGN, PLUS, MINUS, LPAREN, RPAREN, LESS_THAN, GREATER_THAN, MULTIPLY, DIVISION,
    AUTO, BREAK, CASE, CHAR, CONST, CONTINUE, DEFAULT, DO, DOUBLE, ELSE, ENUM, EXTERN, FLOAT, FOR, GOTO, IF,
    INLINE, INT_KW, LONG, REGISTER, RESTRICT, RETURN, SHORT, SIGNED, SIZEOF, STATIC, STRUCT, SWITCH, TYPEDEF,
    UNION, UNSIGNED, VOID, VOLATILE, WHILE
};

unordered_map<string, TokenType> keyword_map = {
    {"auto", TokenType::AUTO}, {"break", TokenType::BREAK}, {"case", TokenType::CASE}, {"char", TokenType::CHAR},
    {"const", TokenType::CONST}, {"continue", TokenType::CONTINUE}, {"default", TokenType::DEFAULT},
    {"do", TokenType::DO}, {"double", TokenType::DOUBLE}, {"else", TokenType::ELSE}, {"enum", TokenType::ENUM},
    {"extern", TokenType::EXTERN}, {"float", TokenType::FLOAT}, {"for", TokenType::FOR}, {"goto", TokenType::GOTO},
    {"if", TokenType::IF}, {"inline", TokenType::INLINE}, {"int", TokenType::INT_KW}, {"long", TokenType::LONG},
    {"register", TokenType::REGISTER}, {"restrict", TokenType::RESTRICT}, {"return", TokenType::RETURN},
    {"short", TokenType::SHORT}, {"signed", TokenType::SIGNED}, {"sizeof", TokenType::SIZEOF},
    {"static", TokenType::STATIC}, {"struct", TokenType::STRUCT}, {"switch", TokenType::SWITCH},
    {"typedef", TokenType::TYPEDEF}, {"union", TokenType::UNION}, {"unsigned", TokenType::UNSIGNED},
    {"void", TokenType::VOID}, {"volatile", TokenType::VOLATILE}, {"while", TokenType::WHILE}
};

const string token_names[] = {
    "ILLEGAL", "END", "IDENT", "INT", "ASSIGN", "PLUS", "MINUS", "LPAREN", "RPAREN",
    "LESS_THAN", "GREATER_THAN", "MULTIPLY", "DIVISION",
    "AUTO", "BREAK", "CASE", "CHAR", "CONST", "CONTINUE", "DEFAULT", "DO",
    "DOUBLE", "ELSE", "ENUM", "EXTERN", "FLOAT", "FOR", "GOTO", "IF", "INLINE",
    "INT_KW", "LONG", "REGISTER", "RESTRICT", "RETURN", "SHORT", "SIGNED",
    "SIZEOF", "STATIC", "STRUCT", "SWITCH", "TYPEDEF", "UNION", "UNSIGNED",
    "VOID", "VOLATILE", "WHILE"
};

struct Token {
    TokenType type;
    string value;
    int line;
    int column;
};

class Lexer {
public:
    Lexer(string file_name) : current_pos(0), next_pos(0), line_number(1), column_number(0) {
        ifstream file(file_name);
        if (file.is_open()) {
            source_code = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
            file.close();
        }
        input_length = source_code.size();
        advance_char();
    }
    Token next_token();

private:
    string source_code;
    int input_length;
    int current_pos;
    int next_pos;
    int line_number;
    int column_number;
    char current_char;
    void advance_char();
    void skip_whitespace();
    Token read_identifier();
    Token read_number();
    TokenType lookup_identifier(const string &identifier);
};

void Lexer::advance_char() {
    if (next_pos >= input_length) {
        current_char = 0;
    } else {
        current_char = source_code[next_pos];
    }
    if (current_char == '\n') {
        line_number++;
        column_number = 0;
    } else {
        column_number++;
    }
    current_pos = next_pos++;
}

void Lexer::skip_whitespace() {
    while (isspace(current_char)) {
        advance_char();
    }
}

TokenType Lexer::lookup_identifier(const string &identifier) {
    if (keyword_map.find(identifier) != keyword_map.end()) {
        return keyword_map[identifier];
    }
    return TokenType::IDENT;
}

Token Lexer::read_identifier() {
    string ident_value;
    int start_column = column_number;
    while (isalpha(current_char)) {
        ident_value += current_char;
        advance_char();
    }
    return {lookup_identifier(ident_value), ident_value, line_number, start_column};
}

Token Lexer::read_number() {
    string num_value;
    int start_column = column_number;
    while (isdigit(current_char)) {
        num_value += current_char;
        advance_char();
    }
    return {TokenType::INT, num_value, line_number, start_column};
}

Token Lexer::next_token() {
    skip_whitespace();
    Token token;
    int start_column = column_number;
    switch (current_char) {
        case '=':
            token = {TokenType::ASSIGN, string(1, current_char), line_number, column_number};
            break;
        case '+':
            token = {TokenType::PLUS, string(1, current_char), line_number, column_number};
            break;
        case '-':
            token = {TokenType::MINUS, string(1, current_char), line_number, column_number};
            break;
        case '(':
            token = {TokenType::LPAREN, string(1, current_char), line_number, column_number};
            break;
        case ')':
            token = {TokenType::RPAREN, string(1, current_char), line_number, column_number};
            break;
        case '<':
            token = {TokenType::LESS_THAN, string(1, current_char), line_number, column_number};
            break;
        case '>':
            token = {TokenType::GREATER_THAN, string(1, current_char), line_number, column_number};
            break;
        case '*':
            token = {TokenType::MULTIPLY, string(1, current_char), line_number, column_number};
            break;
        case '/':
            token = {TokenType::DIVISION, string(1, current_char), line_number, column_number};
            break;
        case 0:
            token = {TokenType::END, "", line_number, column_number};
            break;
        default:
            if (isalpha(current_char)) return read_identifier();
            if (isdigit(current_char)) return read_number();
            token = {TokenType::ILLEGAL, string(1, current_char), line_number, column_number};
    }
    advance_char();
    return token;
}

int main(int argc, char **argv) {
    string file_name = argv[1];
    Lexer lexer(file_name);
    Token token;
    
    do {
        token = lexer.next_token();
        cout << token.value << "\t" << token_names[static_cast<int>(token.type)] << "\t(Row: " << token.line << ", Col: " << token.column << ")" << endl;
    } while (token.type != TokenType::END);

    return 0;
}