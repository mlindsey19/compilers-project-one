#include <stdio.h>
#include "tests.h"
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <getopt.h>


int main (int argc, char **argv){
//    testSimpleStreams();
//    testGetEOFtk();
//    testINTtks();
//    testOPtks();
//    testIDENTtks();
//    testMultipleTks();
//    testKeywordTKs();
//    testLineNumbers();
//    testCommentStreams();
//    int c,j;
//
//    opterr = 0;
//    while ((c = getopt(argc, argv, "t")) != -1)
//        switch (c) {
//            case 't':
//                testSimpleStreams();
//                testGetEOFtk();
//                testINTtks();
//                testOPtks();
//                testIDENTtks();
//                testMultipleTks();
//                testKeywordTKs();
//                testLineNumbers();
//                testCommentStreams();
//            default:
//                abort();
//        }
    FILE * fp;
    char infile[32];
    char *ext = ".input1";



    if (argc == 1)
        fp = stdin;
    else {
        strcpy(infile, argv[1]);
        char *pos = strstr(infile, ext);
        if(pos == NULL)
            strcat(infile,ext);
        strcat(infile, "\0");
        fp = fopen(infile, "r");
    }

    scanner(fp);
    fclose(fp);

    int j = 0;
    while(1){
        printf("%s\n", tokenList[ j ].instance);
        if( !strcmp( tokenList[ j++ ].instance, "EOFtk" ) )
            break;
    }
    free(tokenList);

    return 0;
}