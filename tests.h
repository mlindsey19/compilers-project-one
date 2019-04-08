//
// Created by mlind on 3/4/2019.
//

#ifndef SCANNER_TESTS_H
#define SCANNER_TESTS_H

#include <stdio.h>
#include "token.h"
void testSimpleStreams();
void testGetEOFtk();
void testINTtks();
void testOPtks();
void testIDENTtks();
void testMultipleTks();
void testKeywordTKs();
void testLineNumbers();
void testCommentStreams();

//from scanner
extern Token *tokenList;
void scanner(FILE * stream);






#endif //SCANNER_TESTS_H
