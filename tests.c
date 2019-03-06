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

static int testOneCharStream(char[]);
static int isEOFtk(Token );
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
    assert(isEOFtk(tokenList[0]) && "did not get end of file token back");
}

static int testOneCharStream(char string[]){
    int  ch;
    stream = fmemopen(string, strlen(string), "r");
    ch = fgetc(stream);
    fclose(stream);
    return ch;
}

static int isEOFtk(Token token){
    assert(token.lineNumber >= 0 && "why is there a negative line number?");
    int isTrue = token.id == EOFtk ? 1 : 0;
    return isTrue;
}
static int numberOfTokens(){
    return sizeof(tokenList)/ sizeof(Token );
}
static void freeTokenList() {
    free(tokenList);
}