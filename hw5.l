    /* hw3 */
%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include "hash.h"
    void yyerror(char *);

    struct symbol_node *symbols[100000];
    int length = 0; 
    int line_numbers = 1;
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

[\n] {
    line_numbers++;
}


[a-zA-Z][0-9a-zA-Z_]*       {
                //yylval.string = strdup(yytext);
                yylval.symbol = lookup(yytext);
                if (yylval.symbol->line_update == NULL || strcmp(yylval.symbol->line_update, "yes") != 0)
                {
                    yylval.symbol->line = line_numbers;
                    yylval.symbol->line_update = "yes";
                }
                
                return ID;
                }

[0-9]+      {
                yylval.number = atoi(yytext);
                return INTEGER;
            }

[\"][^\"]*[\"]     {
                char * dummy = strdup(yytext);
                int str_len = strlen(dummy);
                memmove(&dummy[0], &dummy[1], str_len);
                str_len--;
                memmove(&dummy[str_len-1], &dummy[str_len], str_len);
                yylval.string = dummy;
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
[ \t]   ;       /* skip whitespace */

.   {
        return UNKNOWN;
    }

%%

int yywrap(void) {
    return 1;
}
