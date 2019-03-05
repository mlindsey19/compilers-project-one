//
// Created by mlind on 3/5/2019.
//

#include <bits/types/FILE.h>
#include "scanner.h"
#include <stdio.h>

Token scanner(FILE * stream){
    Token token;
    token =  (Token){EOFtk, "", 0};
    return token;
}