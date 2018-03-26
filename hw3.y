%{
    #include <stdio.h>
    #include "struct_funcs.h"
    int yylex(void);
    void yyerror(char *);
    int yydebug = 1;
    FILE *yyin;

    struct ast_node * mk_ast_number_node (int value);
    struct ast_node * mk_ast_node (int node_type, struct ast_node * left, struct ast_node * right);
    struct ast_node * mk_ast_symbol_reference_node (struct symbol_node * symbol);
    struct ast_node * mk_ast_assignment_node (struct symbol_node * symbol, struct ast_node * value);
    void print_tree(struct ast_node * node);


%}

%token STRING
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

%union 
{
        int number;
        struct ast_node * ast;
        struct symbol_node * symbol;
}

%token <number> INTEGER
%token <symbol> ID

%type <ast> statements statement expr listexpr term

%%

program:
        program statements          { print_tree($2); }
        | 
        ;
statements:
        statements statement            { $$ = mk_ast_node('S',$1, $2);}
        | statement                     { $$ = $1; }
statement:
        ID '=' expr ';'                     {$$= mk_ast_assignment_node($1, $3); }
        | PRINT '(' listexpr ')' ';'        //{$$ = mk_}
        | PRINTLN '(' listexpr ')' ';'      //{$$=$3; printf("%d\n", $3); }
        | '{' statements '}'
        | IF expr statements
        | IF expr statements ELSE statements
        | WHILE expr statements
        ;
listexpr:
        listexpr ',' expr           //{ printf("%d\n", $3); }
        | expr                      //{ printf("%d\n", $1); }
        ;
expr:
    expr '+' term           {$$ = mk_ast_node('+', $1, $3); }
    | expr '-' term         {$$ = mk_ast_node('+', $1, $3); }
    | expr '*' term         {$$ = mk_ast_node('+', $1, $3); }
    | expr AND term         {$$ = mk_ast_node('A', $1, $3); }
    | expr OR term          {$$ = mk_ast_node('O', $1, $3); }
    | expr EQUALS term      {$$ = mk_ast_node('E', $1, $3); }
    | expr '<' term     {$$ = mk_ast_node('<', $1, $3); }
    | term          {$$ = $1;}
    ;

term:
    FOR ID IN '[' INTEGER ',' INTEGER ']' SUM '(' expr ')'
    | '(' expr ')'    {$$ = $2;}
    | INTEGER       {$$ = mk_ast_number_node($1);}
    | STRING        //{$$ = mk_ast_string_node($1);}
    | ID            {$$ = mk_ast_symbol_reference_node($1); }
    ;


%%



void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");
    yyparse();
    fclose(yyin);
    return 0;
}

void print_tree(struct ast_node * node) {
    fprintf(stderr, "test");
}