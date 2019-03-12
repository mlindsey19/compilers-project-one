//
// Created by mlind on 3/5/2019.
//

#include <bits/types/FILE.h>
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

static void finalState();
static void checkSpace();
static Token newToken( enum TokenID );
static void getNextCharacter( FILE * );
static void digitState();
static void letterState();
static void operatorState();
static void setInstance( enum TokenID );





Token * tokenList;
typedef struct { int strlen, line, tk; } Count;
static  Count count = { 0 , 0 , 0 };
char instance[ 32 ];
typedef struct { char this, next; } Character;
Character character = { SPACE, SPACE };
static enum CharacterRank getRank( char );
enum TokenID currentTkID;




void scanner( FILE * stream ){
    int i, space;
    count.line = count.strlen = count.tk = 0;

    space = 32;
    tokenList = ( Token * ) malloc( sizeof( Token ) * space );
    for( i = 0 ; i < 3 ; i++ ) {
        getNextCharacter( stream );
        switch ( getRank( character.this ) ){
            case digit:
                digitState();
                break;
            case letter:
                letterState();
                break;
            case operator:
                operatorState();
                break;
            case endOfFile:
                finalState();
            default:
                ;
        }

    }
}

static void digitState(){
    instance[ count.strlen++ ] = character.this;
    int rank = getRank(character.next);
    if ( rank == whitespace || rank == endOfFile )
        finalState();
}
static void letterState(){
    instance[ count.strlen++ ] = character.this;
    int rank = getRank(character.next);
    if ( rank == whitespace || rank == endOfFile )
        finalState();
}

static void operatorState(){
    instance[ count.strlen++ ] = character.this;
    int rank = getRank(character.next);
    if ( rank == whitespace || rank == endOfFile || rank == digit || rank == letter || rank == operator)
        finalState();
}

/*********************************************
 * get next char and assign character to next
 * if charter was end of
 *********************************************/
static void getNextCharacter( FILE * stream ){
    if (ftell(stream) == 0)
        character.next = ( char ) fgetc( stream );
    character.this = character.next;
    if ( character.this != EOF )
        character.next = ( char ) fgetc( stream );

    if ( count.strlen == 0 ){
        switch ( getRank( character.this ) ){
            case letter:
                if ( islower( character.this ) )
                    printf("id token must start with upper case. line: %i\n",count.line);
                currentTkID = IDENTtk;
                break;
            case operator:
                currentTkID = OPtk;
                break;
            case digit:
                currentTkID = INTtk;
                break;
            case endOfFile:
                currentTkID = EOFtk;
        }
    }
}


/*********************************************
 * final state -
 * determine which token to create and append
 * to token array
 ********************************************/
static void finalState(){
       tokenList[ count.tk++ ] = newToken( currentTkID );

//    if( character.this == EOF ) {
//        tokenList[ count.tk++ ] = newToken( EOFtk );
//    }else if( getRank( character.this ) == digit ){
//        tokenList[ count.tk++ ] = newToken( INTtk );
//    } else if( getRank( character.this ) == operator ){
//        tokenList [ count.tk ++ ] = newToken( OPtk );
//    } else if( getRank( character.this ) == letter ){
//        tokenList [ count.tk ++ ] = newToken( IDENTtk );
//    }
    count.strlen = 0;
}

static Token newToken( enum TokenID tkid ){
    Token token;
    token.id = tkid;
    setInstance(tkid);
    strcpy(token.instance, instance);
    token.lineNumber = count.line;

    // reset c.strlen, instance
    count.strlen = 0;
    memset( instance, 0, sizeof( instance ) );

    return token;
}
static void getOperatorString(){
    switch ( *instance ){
        case PLUS_tk:
            strcpy(instance, toString(PLUS_tk) );
            break;
    }
}
static void setInstance(enum TokenID tkid){
    if (tkid == EOFtk){
        count.strlen = 6;
        strcpy(instance, "EOFtk" );
    } else if (tkid == OPtk){
        getOperatorString();
    }
}
static enum CharacterRank getRank( char ch ){
    enum CharacterRank rank;

    if ( ch == 92 ){
        rank = comment;
    } else if ( ch >= 48 && ch <= 57 ){
        rank = digit;
    }else if(( ch >= 65 && ch <= 90 ) ||
             ( ch >= 97 && ch <= 122 ) ){
        rank = letter;
    } else if ( ( ch >= 58 && ch <= 62 )||
                ( ch >= 40 && ch <= 74 )||
                ch == 37 || ch == 123 ||
                ch == 125 || ch == 91 ||
                ch == 93 ){
        rank = operator;
    } else if ( ( ch >= 9 && ch <= 13 )||  //tab,newline,line tab, form feed, carriage return
                ch == 32 ) {
        rank = whitespace;
    }else if( ch == EOF ) {
        rank = endOfFile;
    }else
        rank = notInAlphabet;

    return rank;
}


