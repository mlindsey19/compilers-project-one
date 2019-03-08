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

#endif //SCANNER_TOKEN_H
