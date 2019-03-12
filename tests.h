//
// Created by mlind on 3/4/2019.
//

#ifndef SCANNER_TESTS_H
#define SCANNER_TESTS_H

#include "token.h"
void testSimpleStreams();
void testGetEOFtk();
void testINTtks();
void testOPtks();
void testIDENTtks();

//from scanner
extern Token *tokenList;
void scanner(FILE * stream);






#endif //SCANNER_TESTS_H
