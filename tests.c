//
// Created by mlind on 3/4/2019.
//

#include <bits/types/FILE.h>
#include <stdio.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include "tests.h"




static int testOneCharStream( char[] );
static int isCorrectTkID( Token, enum TokenID );
static void freeTokenList();
static void testReturnToken( char[] );

FILE * stream;

char emptyStream[] = "";
char oneSpaceStream[] = " ";
char newLineStream[] = "\n";
void testSimpleStreams(){
    assert( ( testOneCharStream( emptyStream ) == EOF ) && "Empty stream did not return EOF");
    assert( ( testOneCharStream( newLineStream ) == EOL ) && "new line did not return EOL");
    assert( ( testOneCharStream( oneSpaceStream ) == SPACE ) && "Empty stream did not return SPACE");
}

void testGetEOFtk(){
    testReturnToken( emptyStream ); // calls scanner so clean up after test
    assert( isCorrectTkID( tokenList[ 0 ], EOFtk ) && "did not get end of file token back");
    freeTokenList();
}


char singleINTStream[] = "9";
char twoDigitINTStream[] = "95";

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

char plusTKstream[] = "+";
char twoplusTKstream[] = "+ +";
char twoplusTKstream2[] = "++";

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
char simpleIDENTstram[] = "W";
char badIDENTstram[] = "w";
char len3IDENTstram[] = "WWW";
char twoIDENTstram[] = "W W";

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

char WWWplus33AbCtksStream[] = "WWW + 33 Ab C ";

void testMultipleTks(){
    testReturnToken(WWWplus33AbCtksStream);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && "did not return simple WWW IDENT token in multi" );
    assert( isCorrectTkID( tokenList[ 1 ], OPtk) && "did not return simple + op token in multi" );
    assert( isCorrectTkID( tokenList[ 2 ], INTtk) && "did not return simple 33 INt token in multi" );
    assert( isCorrectTkID( tokenList[ 3 ], IDENTtk) && "did not return simple Ab IDENT token in multi" );
    assert( isCorrectTkID( tokenList[ 4 ], IDENTtk) && "did not return simple C IDENT token in multi" );
    assert( isCorrectTkID( tokenList[ 5 ], EOFtk ) && "did not get end of file token back in multi" );
    int j = 0 ;
    for(; j < 6 ; j++){
        printf("%s\n", tokenList[ j ].instance);
    }
    freeTokenList();
}
char beginKWtkstream[] = "Begin";
char multikeywordsstream[] = "Let IFF Program Loop";
void testKeywordTKs(){
    testReturnToken(beginKWtkstream);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && "did not return begin token" );
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token after begin tk" );
    printf("%s\n", tokenList[ 0 ].instance);

    freeTokenList();

    testReturnToken(multikeywordsstream);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && "did not return let token" );
    assert( isCorrectTkID( tokenList[ 1 ], IDENTtk) && "did not return IFF token" );
    assert( isCorrectTkID( tokenList[ 2 ], IDENTtk) && "did not return Program token" );
    assert( isCorrectTkID( tokenList[ 3 ], IDENTtk) && "did not return loop token" );
    assert( isCorrectTkID( tokenList[ 4 ], EOFtk ) && "did not get end of file token after multi keyword");
    freeTokenList();

}

char twolinestream[] = "A\nB";
char mulitilinestream[] = "1 \n 2 \n3\n4";
void testLineNumbers(){
    testReturnToken(twolinestream);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk) && tokenList[0].lineNumber == 1
            && "did not return 'A' token" );
    assert( isCorrectTkID( tokenList[ 1 ], IDENTtk) && tokenList[1].lineNumber == 2
            && "did not return 'B' token" );
    assert( isCorrectTkID( tokenList[ 2 ], EOFtk ) && "did not get end of file token two line");

    freeTokenList();

    testReturnToken(mulitilinestream);
    assert( isCorrectTkID( tokenList[ 0 ], INTtk) && tokenList[0].lineNumber == 1
            && "did not return 1 token" );
    assert( isCorrectTkID( tokenList[ 1 ], INTtk) && tokenList[1].lineNumber == 2
            && "did not return 2 token" );
    assert( isCorrectTkID( tokenList[ 2 ], INTtk)&& tokenList[2].lineNumber == 3
            && "did not return 3 token" );
    assert( isCorrectTkID( tokenList[ 3 ], INTtk)&& tokenList[3].lineNumber == 4
            && "did not return 4 token" );
    assert( isCorrectTkID( tokenList[ 4 ], EOFtk) && tokenList[4].lineNumber == 4
            && "did not return eof tk multi lin token" );

    freeTokenList();

}


char commentStream[] = "\\";
char commentandtkstream[] = "AB\\";
char commentand2tkstream[] = "AB\\BA";
char commentmultilinestream[] = "A\\alskjnierbuaybk skbjfd 43 3k45b 3 \n + 234\\6";

void testCommentStreams(){
    testReturnToken(commentStream);
    assert( isCorrectTkID( tokenList[ 0 ], EOFtk ) && "did not get end of file token after comment");
    freeTokenList();

    testReturnToken(commentandtkstream);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk ) && "did not get AB tk before comment");
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token after comment and tk");

    freeTokenList();

    testReturnToken(commentand2tkstream);
    assert( isCorrectTkID( tokenList[ 0 ], IDENTtk ) && "did not get AB tk before comment");
    //should skip and only return eof
    assert( isCorrectTkID( tokenList[ 1 ], EOFtk ) && "did not get end of file token after comment with tk after");

    freeTokenList();
    testReturnToken(commentmultilinestream);
    assert(isCorrectTkID(tokenList[ 0 ], IDENTtk)  && "no token for A before comment");
    assert(isCorrectTkID(tokenList[ 1 ], OPtk)   && tokenList[1].lineNumber == 2
           && "no optk after comment");
    assert( isCorrectTkID( tokenList[ 2 ], INTtk ) && "did not get end of file token after comment with tk after");
    assert( isCorrectTkID( tokenList[ 3 ], EOFtk ) && "did not get end of file token after comment with tk after");
    int j =0;
    while(1){

        printf("%s\n", tokenList[ j ].instance);
        if( !strcmp( tokenList[ j++ ].instance, "EOFtk" ) )
            break;
    }
    freeTokenList();

}





/***************************************************
 * free memory after each test
 *
 **************************************************/
static void freeTokenList() {
    free(tokenList);
}

static void testReturnToken( char string[] ){
    stream = fmemopen( string, strlen( string ), "r" );
    scanner( stream );
    fclose( stream );
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