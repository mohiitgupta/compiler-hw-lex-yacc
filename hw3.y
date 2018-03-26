%{
    #include <stdio.h>
    #include "hash.h"
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
        char * string;
}

%token <number> INTEGER
%token <symbol> ID
%token <string> STRING

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
        | PRINT '(' listexpr ')' ';'        {$$ = mk_ast_node('p', $3, NULL); }
        | PRINTLN '(' listexpr ')' ';'      {$$ = mk_ast_node('P', $3, NULL); }
        | '{' statements '}'                {$$ = $2;}
        | IF expr statements                {$$ = mk_ast_if_node($2, $3, NULL);}
        | IF expr statements ELSE statements    {$$ = mk_ast_if_node($2, $3, $5);}
        | WHILE expr statements             {$$ = mk_ast_while_node($2, $3);}
        ;
listexpr:
        listexpr ',' expr           { $$ = mk_ast_node ('L', $1, $3);}
        | expr                      { $$ = $1; }
        ;
expr:
    expr '+' term           {$$ = mk_ast_node('+', $1, $3); }
    | expr '-' term         {$$ = mk_ast_node('-', $1, $3); }
    | expr '*' term         {$$ = mk_ast_node('*', $1, $3); }
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
    | STRING        {$$ = mk_ast_string_node($1);}
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
    printf("length is %d", length);
    for (int i=0; i < length; i++) {
        printf("%s", symbols[i]->name);
        printf("%d", symbols[i]->value);
    }

    //traverse(node);
    //fprintf(stderr, "tree test");
}

/*struct ast_node * traverse(struct ast_node * node) {
    if (node == NULL) {
        return NULL;
    }
    
    //struct ast_node * right = traverse(node->right);

    switch (node->node_type)
    {
        case '+':
            struct ast_number_node * left = traverse(node->left);
            struct ast_number_node * right = traverse(node->right);
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            result->value = left->value + left-> right;
            return result;

        case '-';
        case '*':
        case 'A':


            
    }

}*/