%{
    #include <stdio.h>
    #include "hash.h"
    #include <stdlib.h>
    #include "util.h"
    //#include <stdbool.h>
    int yylex(void);
    void yyerror(char *);
    int yydebug = 1;
    FILE *yyin;

    struct ast_node * mk_ast_number_node (int value);
    struct ast_node * mk_ast_node (int node_type, struct ast_node * left, struct ast_node * right);
    struct ast_node * mk_ast_symbol_reference_node (struct symbol_node * symbol);
    struct ast_node * mk_ast_assignment_node (struct symbol_node * symbol, struct ast_node * value);
    void print_tree(struct ast_node * node);
    struct ast_node * traverse(struct ast_node * node);
    int add_value(struct ast_node * value_node);
    struct ast_node * mk_ast_for_sum_node (struct symbol_node * symbol, int left_value, int right_value, struct ast_node * expression);
    struct ast_node * mk_ast_boolean_node (int value);


%}

%token AND
%token OR
%token EQUALS
%token FOR
%token IN
%token SUM
%token PRINT
%token PRINTLN
%token UNKNOWN
%token IF
%token ELSE
%token WHILE
%token INT
%token BOOL
%token STRING_TOKEN

%union 
{
        int number;
        int boolean;
        struct ast_node * ast;
        struct symbol_node * symbol;
        char * string;
}

%token <number> INTEGER
%token <symbol> ID
%token <string> STRING
%token <boolean> BOOLEAN

%type <ast> statements statement expr listexpr term expr2 expr3 expr4 expr5 expr6 idlist idexpr

%%

program:
        /*program*/ statements          { print_tree($1); }
        //| 
        ;
statements:
        statements statement            { $$ = mk_ast_node('S',$1, $2);}
        | statement                     { /*printf("");*/$$ = $1; }
statement:
        ID '=' expr ';'                     {/*printf("");*/$$= mk_ast_assignment_node($1, $3); }
        | PRINT '(' listexpr ')' ';'        {/*printf("");*/$$ = mk_ast_node('p', $3, NULL); }
        | PRINTLN '(' listexpr ')' ';'      {$$ = mk_ast_node('P', $3, NULL); }
        | '{' statements '}'                {/*printf("");*/$$ = $2;}
        | IF expr statement                {/*printf("");*/$$ = mk_ast_if_node($2, $3, NULL);}
        | IF expr statement ELSE statement    {$$ = mk_ast_if_node($2, $3, $5);}
        | WHILE expr statement             {$$ = mk_ast_while_node($2, $3);}
        | INT idlist ';'                {$$ = mk_ast_node('i', $2, NULL);}
        | BOOL idlist ';'               {$$ = mk_ast_node('b', $2, NULL);}
        | STRING_TOKEN idlist ';'       {$$ = mk_ast_node('c', $2, NULL);}
        ;

idlist:
        idlist ',' idexpr           {$$ = mk_ast_node('l', $1, $3);}
        | idexpr               {$$ = $1;}
        ;
idexpr:
        ID              {$$ = mk_ast_symbol_reference_node($1);}

listexpr:
        listexpr ',' expr           { $$ = mk_ast_node ('L', $1, $3);}
        | expr                      { $$ = $1; }
        ;

expr:
    expr OR expr2          {$$ = mk_ast_node('O', $1, $3); }
    | expr2 {$$ = $1;}
    ;
expr2:
    expr2 AND expr3        {$$ = mk_ast_node('a', $1, $3); }
    | expr3 {$$ = $1;}
    ;
expr3:
    expr3 EQUALS expr4      {$$ = mk_ast_node('E', $1, $3); }
    | expr4 {$$ = $1;}
    ;
expr4:
    expr4 '<' expr5     {$$ = mk_ast_node('<', $1, $3); }
    | expr5             {$$ = $1;}
    ;
expr5:
    expr5 '+' expr6           {$$ = mk_ast_node('+', $1, $3); }
    | expr5 '-' expr6         {$$ = mk_ast_node('-', $1, $3); }
    | expr6         {$$ = $1;}
    ;
expr6:
    expr6 '*' term         {$$ = mk_ast_node('*', $1, $3); }
    | term  {$$ = $1;}
    ;

term:
    FOR ID IN '[' INTEGER ',' INTEGER ']' SUM '(' expr ')'  {/*printf("");*/$$ = mk_ast_for_sum_node($2, $5, $7, $11);}
    | '(' expr ')'    {$$ = $2;}
    | INTEGER       {$$ = mk_ast_number_node($1);}
    | STRING        {$$ = mk_ast_string_node($1);}
    | ID            {$$ = mk_ast_symbol_reference_node($1); }
    | BOOLEAN       {$$ = mk_ast_boolean_node($1);}
    //| NULL_VAL      {$$ = mk_ast_string_node("");}
    ;

%%
void yyerror(char *s) {
    fprintf(stderr, "Syntax Error\n");
}

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    return 0;
}

void print_tree(struct ast_node * node) {
    //printf("length is %d", length);
    //struct symbol_node * sym_node = lookup("a");
    //sym_node->value = 4;
    /*for (int i=0; i < length; i++) {
        printf("%s", symbols[i]->name);
        printf("%d", symbols[i]->value);
        printf("%s", symbols[i]->initialize);
        printf("%s", symbols[i]->string_val);
        printf("\n");
    }*/

    traverse(node);

    // for (int i=0; i < length; i++) {
    //     printf("%s ", symbols[i]->name);
    //     int * number = ((int *)symbols[i]->value);
    //     printf("%d ", *number);
    //     printf("%s ", symbols[i]->type);
    //     //printf("%s ", symbols[i]->string_val);
    //     printf("\n");
    // }
    //fprintf(stderr, "tree test");
}

