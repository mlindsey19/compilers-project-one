//
// Created by mlind on 3/5/2019.
//

#ifndef SCANNER_SCANNER_H
#define SCANNER_SCANNER_H

#include "token.h"

void scanner(FILE * stream);
enum CharacterRank{
    digit,
    upCaseLetter,
    letter,
    operator,
    comment,
    notInAlphabet,
    whitespace,
    endOfFile,
    newLine,
    newState
};

#endif //SCANNER_SCANNER_H
