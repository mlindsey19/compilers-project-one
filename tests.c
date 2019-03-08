//
// Created by mlind on 3/4/2019.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include "tests.h"
#include "scanner.h"

static char emptyStream[] = "";
static char oneSpaceStream[] = " ";
static char newLineStream[] = "\n";
static Token mockEOFtk = {EOFtk, EOF, 0};
static char singleINTStream[] = "9";
static char twoDigitINTStream[] = "95";


static int testOneCharStream(char[]);
static int isCorrectTkID(Token, enum TokenID);
static void freeTokenList();


FILE * stream;


void testSimpleStreams(){
    assert((testOneCharStream(emptyStream) == EOF) && "Empty stream did not return EOF");
    assert((testOneCharStream(newLineStream) == EOL) && "new line did not return EOL");
    assert((testOneCharStream(oneSpaceStream) == SPACE) && "Empty stream did not return SPACE");
}
static void testReturnToken(char string[]){
    stream = fmemopen(string, strlen(string), "r");
    scanner(stream);
    fclose(stream);
}

void testGetEOFtk(){
    testReturnToken(emptyStream); // calls scanner so clean up after test
    assert(isCorrectTkID(tokenList[0], EOFtk) && "did not get end of file token back");
    freeTokenList();
}

static int testOneCharStream(char string[]){
    int  ch;
    stream = fmemopen(string, strlen(string), "r");
    ch = fgetc(stream);
    fclose(stream);
    return ch;
}

static int isCorrectTkID(Token token, enum TokenID tokenID){
    assert(token.lineNumber >= 0 && "why is there a negative line number?");
    int isTrue = token.id == tokenID ? 1 : 0;
    return isTrue;
}

void testINTtks(){
    testReturnToken(singleINTStream);
    assert( isCorrectTkID(tokenList[0], INTtk) && "did not return INTtk");
    assert(isCorrectTkID(tokenList[1], EOFtk) && "did not get end of file token back after INTtk");
    freeTokenList();
    testReturnToken(twoDigitINTStream);
    assert( isCorrectTkID(tokenList[0], INTtk) && "did not return INTtk");
    assert(isCorrectTkID(tokenList[1], EOFtk) && "did not get end of file token back after twodigit INTtk");
    freeTokenList();
}

/***************************************************
 * free memory after each test
 *
 **************************************************/
static void freeTokenList() {
    free(tokenList);
}
