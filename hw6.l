    /* hw3 */
%{
    #include "y.tab.h"
    #include <stdlib.h>
    #include "hash.h"
    void yyerror(char *);

    struct symbol_node *symbols[100000];
    int length = 0; 
    int line_numbers = 1;
    int block_level = 1;
    struct scope_node *present_scope;
%}
%option yylineno
%%

[f][o][r] {
    //block_level += 1;
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

Input {
    return INPUT;
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

int {
    return INT;
}

bool {
    return BOOL;
}

string {
    return STRING_TOKEN;
}

null {
    char * dummy = "\0";
    yylval.string = dummy;
    return STRING;
}

[\n] {
    line_numbers++;
}

[{] {
    //block_level += 1;
    return *yytext;
}
[}] {
    //block_level -= 1;
    return *yytext;
}

true {
    yylval.boolean = 1;
    return BOOLEAN;
}

false {
    yylval.boolean = 0;
    return BOOLEAN;
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
                //str_len--;
                str_len = strlen(dummy);
                dummy[str_len-1] = dummy[str_len];
                //memmove(dummy, dummy+1, strlen(dummy));
                yylval.string = dummy;
                return STRING;
            }
[=][=]     { return EQUALS; 
                }
[<][=]      {
            return LESS_EQUALS;
}
[>][=]      {
            return GREAT_EQUALS;
}
[!][=]      {
            return NOT_EQUALS;
}
[-+()=<;>,\[\]*]     { return *yytext; 
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
