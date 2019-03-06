//
// Created by mlind on 3/5/2019.
//

#include <bits/types/FILE.h>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

void finalState(int);
void checkSpace(int *);


Token * tokenList;
typedef struct {int ch,ln,tk;} Count;
static  Count count = {0 ,0,0};


void scanner(FILE * stream){
    int i, space;
    int character;

    space = 32;
    tokenList = (Token *)malloc(sizeof(Token) * space);
    for(i = 0; i < 1;i++) {
        checkSpace(&space);
        character = getc(stream);
        if (character == EOF)
            finalState(character);
    }
}
void finalState(int character){

    if(character == EOF) {
        Token token = (Token) {EOFtk, "", count.ln};
        tokenList[count.tk++] = token;
    }


}
void checkSpace(int * space){
    //do something
}