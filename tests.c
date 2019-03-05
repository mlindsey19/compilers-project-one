//
// Created by mlind on 3/4/2019.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include "tests.h"
#include "scanner.h"

static char emptyStream[] = "";
static char oneSpaceStream[] = " ";
static char newLineStream[] = "\n";
static Token mockEOFtk = {EOFtk, EOF, 0};

static int testOneCharStream(char[]);
static int isEOFtk(Token );

FILE * stream;



void testSimpleStreams(){
    assert((testOneCharStream(emptyStream) == EOF) && "Empty stream did not return EOF");
    assert((testOneCharStream(newLineStream) == EOL) && "new line did not return EOL");
    assert((testOneCharStream(oneSpaceStream) == SPACE) && "Empty stream did not return SPACE");
}
static Token testReturnToken(char string[]){
    Token token;
    stream = fmemopen(string, strlen(string), "r");
    token = scanner(stream);
    fclose(stream);
    return token;
}

void testGetEOFtk(){
    assert(isEOFtk(testReturnToken(emptyStream)) && "did not get end of file token back");
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