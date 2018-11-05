%{
#include "scanner.h"
%}

%%

#include|void|int       { return KEYWORD; }
[+/\-*=]                 { return OPERATOR; }
[{}()<>;]                  { return DELIMITER; }
[a-zA-Z][_0-9a-zA-Z]*   { return IDENTIFIER; }
[0-9]+                   { return NUMBER; }
[ \n\t]                 ;
.                       { printf("Unexpected character\n"); }

%%

int yywrap() {
    return 1;
}
