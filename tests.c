//
// Created by mlind on 3/4/2019.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include "tests.h"


static char emptyStream[] = "";
static char oneSpaceStream[] = " ";
static char newLineStream[] = "\n";
static char singleINTStream[] = "9";
static char twoDigitINTStream[] = "95";
static char plusTKstream[] = "+";
static char twoplusTKstream[] = "+ +";
static char twoplusTKstream2[] = "++";








static int testOneCharStream( char[] );
static int isCorrectTkID( Token, enum TokenID );
static void freeTokenList();


FILE * stream;


void testSimpleStreams(){
    assert( ( testOneCharStream( emptyStream ) == EOF ) && "Empty stream did not return EOF");
    assert( ( testOneCharStream( newLineStream ) == EOL ) && "new line did not return EOL");
    assert( ( testOneCharStream( oneSpaceStream ) == SPACE ) && "Empty stream did not return SPACE");
}
static void testReturnToken( char string[] ){
    stream = fmemopen( string, strlen( string ), "r" );
    scanner( stream );
    fclose( stream );
}
void testGetEOFtk(){
    testReturnToken( emptyStream ); // calls scanner so clean up after test
    assert( isCorrectTkID( tokenList[ 0 ], EOFtk ) && "did not get end of file token back");
    freeTokenList();
}
static int testOneCharStream( char string[] ){
    int  ch;
    stream = fmemopen( string, strlen( string ), "r" );
    ch = fgetc( stream );
    fclose( stream );
    return ch;
}
static int isCorrectTkID( Token token, enum TokenID tokenID ){
    assert( token.lineNumber >= 0 && "why is there a negative line number?" );
    int isTrue = token.id == tokenID ? 1 : 0;
    return isTrue;
}
void testINTtks(){
    testReturnToken( singleINTStream );
    assert( isCorrectTkID( tokenList[ 0 ], INTtk ) && "did not return INTtk" );
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token back after INTtk");
    freeTokenList();
    testReturnToken( twoDigitINTStream);
    assert( isCorrectTkID( tokenList[ 0 ], INTtk ) && "did not return  dbl INTtk" );
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token back after two digit INTtk");
    int j =0;
    for(; j < 2 ; j++){
        printf("%s\n", tokenList[j].instance);
    }
    freeTokenList();
}

void testOPtks(){
    testReturnToken(plusTKstream);
    assert(isCorrectTkID( tokenList[0] , OPtk) && "did not return simple plus token");
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token back after two plus tk");

    freeTokenList();
    testReturnToken(twoplusTKstream);
    assert(isCorrectTkID( tokenList[0] , OPtk) && "did not return 1st two plus token");
    assert(isCorrectTkID( tokenList[1] , OPtk) && "did not return  2nd two plus token");
    assert( isCorrectTkID( tokenList[ 2 ], EOFtk ) && "did not get end of file token back after two plus tk");

    freeTokenList();
    testReturnToken(twoplusTKstream2);
    assert(isCorrectTkID( tokenList[0] , OPtk) && "did not return 1st two plus token no space");
    assert(isCorrectTkID( tokenList[1] , OPtk) && "did not return  2nd two plus token no space");
    assert( isCorrectTkID( tokenList[ 2 ], EOFtk ) && "did not get end of file token back after two plus tk no space");

    int j = 0 ;
    for(; j < 3 ; j++){
        printf("%s\n", tokenList[j].instance);
    }
    freeTokenList();
}
static char simpleIDENTstram[] = "W";
static char badIDENTstram[] = "w";
static char len3IDENTstram[] = "WWW";
static char twoIDENTstram[] = "W W";

void testIDENTtks(){
    testReturnToken(simpleIDENTstram);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && "did not return simple IDENT token" );
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token back after simple ident" );
    freeTokenList();

    testReturnToken(len3IDENTstram);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && "did not return WWW token" );
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token back after WWW tk" );
    printf("%s\n", tokenList[ 0 ].instance);

    freeTokenList();

    testReturnToken(twoIDENTstram);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && "did not return 1st two IDENT token ");
    assert( isCorrectTkID( tokenList[ 1 ], IDENTtk) && "did not return  2nd two ident token ");
    assert( isCorrectTkID( tokenList[ 2 ], EOFtk ) && "did not get end of file token back after two ident" );

    int j = 0 ;
    for(; j < 3 ; j++){
        printf("%s\n", tokenList[ j ].instance);
    }
    freeTokenList();

    testReturnToken(badIDENTstram);
    freeTokenList();
}

/***************************************************
 * free memory after each test
 *
 **************************************************/
static void freeTokenList() {
    free(tokenList);
}
