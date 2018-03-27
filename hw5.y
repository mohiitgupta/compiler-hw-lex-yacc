%{
    #include <stdio.h>
    #include "hash.h"
    #include <stdlib.h>
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

%type <ast> statements statement expr listexpr term expr2 expr3 expr4 expr5 expr6

%%

program:
        program statements          { print_tree($2); }
        | 
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
        ;
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
    FOR ID IN '[' INTEGER ',' INTEGER ']' SUM '(' expr ')'  {/*printf("");*/}
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

int add_value(struct ast_node * value_node) {
    if (value_node->node_type == 's') {
        struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        struct symbol_node * result = left->symbol;
        /*if (strcmp(result->initialize, "initialized") == 0) {
            return result->value;
        } else {
            printf("not initialized\n");
        }*/
        if (result->type == NULL) {
            printf("Uninitialized variable in %d\n", result->line);
            exit(0);
        }
        int value = 0;
        if (strcmp(result->type, "number") == 0) {
           value = (int) *(int *)result->value; 
        }
        
        return value;
    } else if (value_node->node_type == 'N') {
        struct ast_number_node * left = (struct ast_number_node *) value_node;
        return left->value;
    }
    return 0;
}

char * get_value(struct ast_node * value_node) {
    char *snum;
    //printf("inside get value block \n");
    if (value_node->node_type == 's') {
        //struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        //struct symbol_node * result = left->symbol;
        //printf("inside symbole reference block in get value\n");
        struct ast_symbol_reference_node * value_symbol_node = (struct ast_symbol_reference_node *) value_node;
        
        struct symbol_node * result = find(value_symbol_node->symbol->name);
        if (result->type == NULL) {
            printf("Uninitialized variable in %d\n", result->line);
            exit(0);
        }
        //printf("name of symbol is %s", result->name);
        if (strcmp(result->type, "number") == 0) {
            snum = (char *)malloc(100);
            int number_dummy = *(int *)result->value;
            //printf("value of %s is %d\n", result->name, number_dummy);
            snprintf(snum, 100, "%d", number_dummy);
            //itoa(number_dummy,snum,10);
        } else if (strcmp(result->type, "string") == 0){
            snum = (char *) malloc(strlen(result->value)+1);
            strcpy(snum, result->value);
        } else {
            printf("not initialized");
        }
        //return snum;
    } else if (value_node->node_type == 'N') {
        struct ast_number_node * left = (struct ast_number_node *) value_node;
        snum = (char *)malloc(100);
        //printf("value of left->value is %d\n",left->value);
        snprintf(snum, 100, "%d", left->value);
        //itoa(left->value,snum,10);
        //return snum;
    }else if (value_node->node_type == 'n') {
        struct ast_string_node * left = (struct ast_string_node *) value_node;
        //fprintf(stderr, "size of string is %lu\n", strlen(left->value));
        snum = (char *)malloc(strlen(left->value)+1);
        strcpy(snum, left->value);
        //return left->value;
    }
    // int len = strlen(snum);
    // snum[len]='\0';
    //fflush(stdin);
    //printf("value of snum is %s\n", snum);
    return snum;
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

struct ast_node * traverse(struct ast_node * ast_tree) {
    if (ast_tree == NULL) {
        return NULL;
    }
    switch (ast_tree->node_type)
    {
        case '+':
        {
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            result->value += add_value(dummy);
            return (struct ast_node *) result;
            break;
        }

        case '-':
        {
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            result->value -= add_value(dummy);
            return (struct ast_node *) result;
            break;
        }

        case '*':
        {
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            result->value *= add_value(dummy);
            return (struct ast_node *) result;
            break;
        }
        case '<':
        {
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) > result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }
        case 'E':
        {
            //printf("equality block came\n");
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) == result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }
        case 'a':
        {
            //printf("and block came\n");
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) && result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }
        case 'O':
        {
            //printf("or block came\n");
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) || result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }

        case 'A':
        {
            struct ast_assignment_node * node = (struct ast_assignment_node *) ast_tree;
            struct symbol_node * sym_node = find(node->symbol->name);
            struct ast_node * value_node = traverse(node->value);
            if (value_node->node_type == 'N') 
            {
                struct ast_number_node * result = (struct ast_number_node *) value_node;
                int * number_dummy = (int*)malloc(sizeof(int));
                *number_dummy = result->value;

                sym_node->value = (void *) number_dummy;
                sym_node->type = "number";
                //printf("value stored in assignment is %d\n", *(int *)sym_node->value);

                //printf("");
                //sym_node->initialize = "initialized";
            } else if (value_node->node_type == 'n')
            {
                struct ast_string_node * result = (struct ast_string_node *) value_node;
                //char * string_dummy = result->value;
                sym_node->value = (char *) malloc(strlen(result->value)+1);
                strcpy(sym_node->value, result->value);
                //sym_node->value = (void *) string_dummy;
                sym_node->type = "string";
                //sym_node->initialize = "initialized";
            } else if (value_node->node_type == 's')
            {
                struct ast_symbol_reference_node * result_sym_node = (struct ast_symbol_reference_node *) value_node;
                struct symbol_node * result = result_sym_node->symbol;
                if (result->type == NULL) {
                    fprintf(stderr, "Uninitialized variable in %d\n", result->line);
                    exit(0);
                }
                if (strcmp(result->type, "number") == 0) {
                    int * number_dummy = malloc(sizeof(int));
                    *number_dummy = *(int *)(result->value);

                    sym_node->value = (void *) number_dummy;
                    sym_node->type = "number";
                } else if (strcmp(result->type, "string") == 0){
                    sym_node->type = "string";
                    sym_node->value = (char *) malloc(strlen(result->value)+1);
                    strcpy(sym_node->value, result->value);
                } else {
                    printf("not initialized");
                }
                //sym_node->value = result->value;
                
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
            struct ast_node * value_node = traverse(ast_tree->left);
            /*if (value_node->node_type == 'n')
            {
                struct ast_string_node * value_string_node = (struct ast_string_node *) value_node;
                printf("%s\n", value_string_node->value);
            } else if (value_node->node_type == 'N') {
                struct ast_number_node * value_number_node = (struct ast_number_node *) value_node;
                char *snum;
                sprintf(snum, "%d", value_number_node->value);
                printf("%s\n", snum);
            } else if (value_node->node_type == 's') {
                struct ast_symbol_reference_node * value_symbol_node = (struct ast_symbol_reference_node *) value_node;
                char *snum;
                struct symbol_node * result = value_symbol_node->symbol;
                if (strcmp(result->type, "number") == 0) {
                    snum = (char *)malloc(100);
                    int number_dummy = *(int *)result->value;
                    sprintf(snum, "%d", number_dummy);
                } else if (strcmp(result->type, "string") == 0){
                    snum = (char *) malloc(strlen(result->value)+1);
                    strcpy(snum, result->value);
                } else {
                    printf("not initialized");
                }
                printf("%s\n", snum);
            }*/
            char * string_value = get_value(value_node);
            fprintf(stderr, "%s \n", string_value);            
            break;
        }
            
        case 'p':
        {
            struct ast_node * value_node = traverse(ast_tree->left);
            char * string_value = get_value(value_node);
            fprintf(stderr, "%s", string_value);
            break;
        }
            
        case 'L':
        {  
            //printf("inside L block\n");
            struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
            result->node_type = 'n';
            struct ast_node * dummy = traverse(ast_tree->left);
            char * value1 = get_value(dummy);
            //printf("value 1 is %s\n", value1);
            struct ast_node * dummy2 = traverse(ast_tree->right);
            char * value2 = get_value(dummy2);
            //printf("value 2 is %s\n", value2);
            result->value = malloc(strlen(value1)+strlen(value2)+1);
            strcpy(result->value, value1);
            strcat(result->value, " ");
            strcat(result->value, value2);
            // printf("value is %s", result->value);
            return (struct ast_node *) result;
            break;
        }
        case 'I':
        {
            struct ast_if_node * if_node = (struct ast_if_node *) ast_tree;
            struct ast_number_node * condition = (struct ast_number_node *) traverse(if_node->condition);
            if (condition->value == 0) {
                traverse(if_node->else_branch);
            } else {
                traverse(if_node->if_branch);
            }
            //printf("if block came");
            break;
        }
        case 'W':
        {
            struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
            struct ast_number_node * condition = (struct ast_number_node *) traverse(while_node->condition);
            while(condition->value != 0) {
                traverse(while_node->while_branch);
                condition = (struct ast_number_node *) traverse(while_node->condition);
            }
            //printf("while block came");
            break;
        }
            
    }
    return ast_tree;
}