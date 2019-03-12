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
    ASTERISK_tk = 42
};


#endif //SCANNER_TOKEN_H
