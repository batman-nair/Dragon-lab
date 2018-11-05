#include <stdio.h>
#include "scanner.h"

extern int yylex();
extern int yylineno;
extern char* yytext;


const char *names[] = {"KEYWORD", "IDENTIFIER", "OPERATOR", "DELIMITER", "NUMBER" };

int main() {

    int token_no = yylex();

    while(token_no) {

        printf(" %s - %s \n", names[token_no-1], yytext);

        token_no = yylex();
    }

    return 0;
}
