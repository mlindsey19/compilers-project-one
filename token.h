//
// Created by mlind on 3/5/2019.
//

#ifndef SCANNER_TOKEN_H
#define SCANNER_TOKEN_H

#define EOL '\n'
#define SPACE ' '

enum tokenID{
    EOFtk,
    EOLtk
};
typedef struct {
    enum tokenID  id;
    char instance[32];
    int lineNumber;
}token;

#endif //SCANNER_TOKEN_H
