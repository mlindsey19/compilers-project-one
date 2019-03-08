//
// Created by mlind on 3/5/2019.
//

#include <bits/types/FILE.h>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

static void finalState(char);
static void checkSpace(int *);
static Token newToken(enum TokenID);



Token * tokenList;
typedef struct {int strlen,line,tk;} Count;
static  Count count = {0 ,0,0};
char instance[64];


void scanner(FILE * stream){
    int i, space;
    char character;

    space = 32;
    tokenList = (Token *)malloc(sizeof(Token) * space);
    for(i = 0; i < 2;i++) {
        //    checkSpace(&space);
        character = getc(stream);
        finalState(character);
        if (character == EOF) {
            count.tk = 0;
            count.line = 0;
            break;
        }

    }
}
/*********************************************
 * final state -
 * determine which token to create and append
 * to token array
 ********************************************/
static void finalState(char character){


    if(character == EOF) {
        count.strlen = 5;
        strncpy(instance, "EOFtk", count.strlen);
        tokenList[count.tk++] = newToken(EOFtk);
    }else if(character >= 48 && character <= 57){
        instance[count.strlen++] = character;
        tokenList[count.tk++] = newToken(INTtk);

    }


}
void checkSpace(int * space){
    //do something
}

static Token newToken(enum TokenID tkid){
    Token token;
    token.id = tkid;
    strncpy(token.instance, instance, (size_t ) count.strlen);
    token.lineNumber = count.line;

    // reset c.strlen, instance
    count.strlen = 0;
    memset(instance, 0, sizeof(instance));

    return token;
}