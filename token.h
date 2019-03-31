//
// Created by mlind on 3/5/2019.
//

#ifndef SCANNER_TOKEN_H
#define SCANNER_TOKEN_H

#define EOL '\n'
#define SPACE ' '

enum TokenID{
    EOFtk,
    OPtk,
    IDENTtk,
    INTtk
};
typedef struct {
    enum TokenID  id;
    char instance[32];
    int lineNumber;
}Token;

#define toString(x) #x
enum Operator{
    PLUS_tk = 43,
    LESS_THAN_tk = 60,
    GREATER_THAN_tk = 62,
    MINUS_tk = 45,
    ASTERISK_tk = 42,
    SLASH_tk = 47,
    PERCENT_tk = 37,
    DOT_tk = 46,
    OPEN_PARENTH_tk = 41,
    CLOSE_PARENTH_tk = 40,
    COMMA_tk = 44,
    OPEN_BRACE_tk = 123,
    CLOSE_BRACE_tk = 125,
    SEMICOLON_tk = 59,
    OPEN_BRACKET_tk = 91,
    CLOSE_BRACKET_tk = 92
};


#endif //SCANNER_TOKEN_H
