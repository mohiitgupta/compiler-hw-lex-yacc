    /* hw3 */
%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include "hash.h"
    void yyerror(char *);
%}

%%

[f][o][r] {
    return FOR;
    }
[S][U][M] {
    return SUM;
    }
[i][n] {
    return IN;
    }
[P][r][i][n][t] {
    return PRINT;
    }
[P][r][i][n][t][l][n] {
    return PRINTLN;
    }

if  {
        return IF;  
    }
else  {
        return ELSE;  
    }
while {
        return WHILE;  
    }


[a-zA-Z][0-9a-zA-Z_]*       {
                //yylval.string = strdup(yytext);
                yylval.symbol = lookup(yytext);
                return ID;
                }

[0-9]+      {
                yylval.number = atoi(yytext);
                return INTEGER;
            }

[\"][^\"]*[\"]     {
                return STRING;
            }
[=][=]     { return EQUALS; 
                }
[-+()=<;,\[\]{}*]     { return *yytext; 
                }
[&][&]        {  return AND; 
                }
[|][|]        { return OR; 
                }

[/]\*([^*]|[\r\n]|([\*]+([^*/]|[\r\n])))*[\*]+[/]   ; /* skip comments */
[/][/][^\n]*  ;    /* skip comments */
[ \t\n]   ;       /* skip whitespace */

.   {
        return UNKNOWN;
    }

%%

int yywrap(void) {
    return 1;
}
