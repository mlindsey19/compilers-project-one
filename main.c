#include <stdio.h>
#include "tests.h"

int main() {

    testSimpleStreams();
    testGetEOFtk();
    testINTtks();
    testOPtks();
    testIDENTtks();
    testMultipleTks();
    testKeywordTKs();
    testLineNumbers();


    return 0;
}