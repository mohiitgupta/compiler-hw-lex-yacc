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
    struct ast_node * traverse(struct ast_node * node);
    int add_value(struct ast_node * value_node);


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

    /*for (int i=0; i < length; i++) {
        printf("%s", symbols[i]->name);
        printf("%d", symbols[i]->value);
        printf("%s", symbols[i]->initialize);
        printf("%s", symbols[i]->string_val);
        printf("\n");
    }*/
    //fprintf(stderr, "tree test");
}

int add_value(struct ast_node * value_node) {
    if (value_node->node_type == 's') {
        struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        struct symbol_node * result = left->symbol;
        if (strcmp(result->initialize, "initialized") == 0) {
            return result->value;
        } else {
            printf("not initialized\n");
        }
    } else if (value_node->node_type == 'N') {
        struct ast_number_node * left = (struct ast_number_node *) value_node;
        return left->value;
    }
    return 0;
}

char * get_value(struct ast_node * value_node) {
    if (value_node->node_type == 's') {
        struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        struct symbol_node * result = left->symbol;
        if (strcmp(result->initialize, "initialized") == 0) {
            return result->string_val;
        } else {
            printf("not initialized\n");
        }
    } else if (value_node->node_type == 'n') {
        struct ast_string_node * left = (struct ast_string_node *) value_node;
        return left->value;
    }
    return "";
}

struct ast_node * traverse(struct ast_node * ast_tree) {
    if (ast_tree == NULL) {
        return NULL;
    }

    //struct ast_node * left = traverse(node->left);
    //struct ast_node * right = traverse(node->right);
    //printf("%c\n",node->node_type);
    //return node;
    switch (ast_tree->node_type)
    {
        case '+':
            //printf("");
            
            //struct ast_number_node * left = (struct ast_number_node *) traverse(ast_tree->left);
            //struct ast_number_node * right = (struct ast_number_node *) traverse(ast_tree->right);
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';

            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            result->value += add_value(dummy);
            //result->value = left->value + right->value;
            return (struct ast_node *) result;
            break;

        /*case '-':
        case '*':*/
        case 'A':
        {
            //printf("");
            struct ast_assignment_node * node = (struct ast_assignment_node *) ast_tree;
            struct symbol_node * sym_node = lookup(node->symbol->name);
            struct ast_node * value_node = traverse(node->value);
            if (value_node->node_type == 'N') 
            {
                struct ast_number_node * result = (struct ast_number_node *) value_node;
                sym_node->value = result->value;
                sym_node->initialize = "initialized";
            } else if (value_node->node_type == 'n')
            {
                struct ast_string_node * result = (struct ast_string_node *) value_node;
                sym_node->string_val = result->value;
                sym_node->initialize = "initialized";
            } else if (value_node->node_type == 's')
            {
                struct ast_symbol_reference_node * result_sym_node = (struct ast_symbol_reference_node *) value_node;
                struct symbol_node * result = result_sym_node->symbol;
                if (strcmp(result->initialize, "initialized") == 0) {
                    sym_node->value = result->value;
                    sym_node->initialize = "initialized";
                } else {
                    printf("not initialized\n");
                }
                
            }
            return ast_tree;
            break;
        }
           

        case 'n':
            return ast_tree;
            break;
        case 'N':
            return ast_tree;
            break;
        case 'S':
            traverse(ast_tree->left);
            traverse(ast_tree->right);
            break;
        case 'P':
        {
            //printf("");
            struct ast_string_node * value_string_node = (struct ast_string_node *) traverse(ast_tree->left);
            printf("%s\n", value_string_node->value);
            break;
        }
            
        case 'p':
        {
            //printf("");
            struct ast_string_node * value_string_node = (struct ast_string_node *) traverse(ast_tree->left);
            printf("%s", value_string_node->value);
            break;
        }
            
        case 'L':
        {  
            //printf("");
            struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
            result->node_type = 'n';
            struct ast_node * dummy = (struct ast_node *) traverse(ast_tree->left);
            char * value1 = get_value(dummy);
            dummy = (struct ast_node *) traverse(ast_tree->right);
            char * value2 = get_value(dummy);
            result->value = malloc(strlen(value1)+strlen(value2)+1);
            strcpy(result->value, value1);
            strcat(result->value, value2);
            return (struct ast_node *) result;
            break;
        }
        case 'I':
        {

        }
            



  
    }
    return ast_tree;
        }

}