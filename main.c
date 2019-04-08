#include <stdio.h>
#include "tests.h"
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <bits/getopt_core.h>


int main (int argc, char **argv){

    int c,j;

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
    j = 0;
    while(1){
        if( strlen( tokenList[ j ].instance ) == 0)
            break;
        printf("%s\n", tokenList[ j++ ].instance);
    }
    free(tokenList);

    fclose(fp);
    return 0;
}