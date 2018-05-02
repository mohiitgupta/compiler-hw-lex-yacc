%{
    #include <stdio.h>
    #include "hash.h"
    #include <stdlib.h>
    #include "util.h"
    #include "live_analysis_util.h"
    // #include "type_util.h"
    //#include <stdbool.h>
    int yylex(void);
    void yyerror(char *);
    int yydebug = 1;
    FILE *yyin;

    struct ast_node * mk_ast_number_node (int value);
    struct ast_node * mk_ast_node (int node_type, struct ast_node * left, struct ast_node * right);
    struct ast_node * mk_ast_symbol_reference_node (struct symbol_node * symbol);
    struct ast_node * mk_ast_assignment_node (struct ast_node * symbol, struct ast_node * value);
    void print_tree(struct ast_node * node);
    struct ast_node * traverse(struct ast_node * node);
    int add_value(struct ast_node * value_node);
    struct ast_node * mk_ast_for_sum_node (struct ast_node * symbol, int left_value, int right_value, struct ast_node * expression);
    struct ast_node * mk_ast_boolean_node (int value);
    struct ast_node * typecheck(struct ast_node * ast_tree);
    // int getOperatorResultNodeType(int node_type);

    int typeError = 0;


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
%token LESS_EQUALS
%token GREAT_EQUALS
%token NOT_EQUALS
%token INPUT


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

%type <ast> statements statement expr listexpr term expr2 expr3 expr4 expr5 expr6 idlist idexpr eq_op plus_op
%type <ast> minus_op multiply_op equals_op less_than_op and_op or_op
%type <ast> print_op println_op if_op while_op less_equals_op great_equals_op great_than_op not_equals_op
%type <ast> bracket_op sum_op inputlist

%%

program:
        /*program*/ statements          { print_tree($1); }
        //| 
        ;
statements:
        statements statement            { $$ = mk_ast_node('S',$1, $2);}
        | statement                     { /*printf("");*/$$ = $1; }
statement:
        idexpr eq_op expr ';'                     {$$= mk_ast_assignment_node($1, $3);
        $$->line_no=$2->line_no;
         /*printf("line number for equals is %d\n", $$->line_no);*/}
        | print_op '(' listexpr ')' ';'        {/*printf("");*/$$ = mk_ast_node('p', $3, NULL);$$->line_no=$1->line_no; }
        | println_op '(' listexpr ')' ';'      {$$ = mk_ast_node('P', $3, NULL);$$->line_no=$1->line_no; }
        | INPUT '(' inputlist ')' ';'          {$$ = mk_ast_node('Q', $3, NULL); }
        | '{' statements '}'                {/*printf("");*/$$ = mk_ast_node('C', $2, NULL);}
        | if_op expr statement                {/*printf("");*/$$ = mk_ast_if_node($2, $3, NULL);
        $$->line_no=$1->line_no;
        // printf("line no of if is %d", $$->line_no);
        /*$$->right=NULL;*/}
        | if_op expr statement ELSE statement    {$$ = mk_ast_if_node($2, $3, $5);$$->line_no=$1->line_no;}
        | while_op expr statement             {$$ = mk_ast_while_node($2, $3);
            $$->line_no=$1->line_no;
            // printf("line no of while is %d", $$->line_no);
        }
        | INT idlist ';'                {$$ = mk_ast_node('i', $2, NULL);}
        | BOOL idlist ';'               {$$ = mk_ast_node('b', $2, NULL);}
        | STRING_TOKEN idlist ';'       {$$ = mk_ast_node('c', $2, NULL);}
        ;

eq_op:
        '='             {$$ = mk_ast_node(0, NULL, NULL);}
print_op:
        PRINT             {$$ = mk_ast_node(0, NULL, NULL);}
println_op:
        PRINTLN             {$$ = mk_ast_node(0, NULL, NULL);}
if_op:
        IF             {$$ = mk_ast_node(0, NULL, NULL);}
while_op:
        WHILE             {$$ = mk_ast_node(0, NULL, NULL);}

inputlist:
        inputlist ',' idexpr    {$$ = mk_ast_node('q', $1, $3);}
        | idexpr        {$$ = $1;}
        ;

idlist:
        idlist ',' idexpr           {$$ = mk_ast_node('l', $1, $3);}
        | idexpr               {$$ = $1;/*printf("line is %d", $$->line_no);*/}
        ;

listexpr:
        listexpr ',' expr           { $$ = mk_ast_node ('L', $1, $3);}
        | expr                      { $$ = $1; }
        ;

expr:
    expr or_op expr2          {$$ = mk_ast_node('O', $1, $3); 
    $$->line_no=$2->line_no; 
}
    | expr2 {$$ = $1;}
    ;
expr2:
    expr2 and_op expr3        {$$ = mk_ast_node('a', $1, $3); 
    $$->line_no=$2->line_no; 
}
    | expr3 {$$ = $1;}
    ;
expr3:
    expr3 equals_op expr4      {$$ = mk_ast_node('E', $1, $3); 
    $$->line_no=$2->line_no;}
    | expr3 not_equals_op expr4      {$$ = mk_ast_node('w', $1, $3); 
    $$->line_no=$2->line_no;}
    | expr4 {$$ = $1;}
    ;
expr4:
    expr4 less_than_op expr5     {$$ = mk_ast_node('<', $1, $3); $$->line_no=$2->line_no;}
    | expr4 great_than_op expr5     {$$ = mk_ast_node('x', $1, $3); $$->line_no=$2->line_no;}
    | expr4 great_equals_op expr5     {$$ = mk_ast_node('y', $1, $3); $$->line_no=$2->line_no;}
    | expr4 less_equals_op expr5     {$$ = mk_ast_node('z', $1, $3); $$->line_no=$2->line_no;}
    | expr5             {$$ = $1;}
    ;
expr5:
    expr5 plus_op expr6           {$$ = mk_ast_node('+', $1, $3); $$->line_no=$2->line_no;}
    | expr5 minus_op expr6         {$$ = mk_ast_node('-', $1, $3); $$->line_no=$2->line_no;}
    | expr6         {$$ = $1;}
    ;
expr6:
    expr6 multiply_op term         {$$ = mk_ast_node('*', $1, $3); $$->line_no=$2->line_no;}
    | term  {$$ = $1;}
    ;

plus_op:
        '+'             {$$ = mk_ast_node(0, NULL, NULL);}
minus_op:
        '-'             {$$ = mk_ast_node(0, NULL, NULL);}
multiply_op:
        '*'             {$$ = mk_ast_node(0, NULL, NULL);}
equals_op:
        EQUALS             {$$ = mk_ast_node(0, NULL, NULL);}
less_than_op:
        '<'             {$$ = mk_ast_node(0, NULL, NULL);}
and_op:
        AND             {$$ = mk_ast_node(0, NULL, NULL);}
or_op:
        OR             {$$ = mk_ast_node(0, NULL, NULL);}
less_equals_op:
        LESS_EQUALS             {$$ = mk_ast_node(0, NULL, NULL);}
great_equals_op:
        GREAT_EQUALS             {$$ = mk_ast_node(0, NULL, NULL);}
not_equals_op:
        NOT_EQUALS             {$$ = mk_ast_node(0, NULL, NULL);}
great_than_op:
        '>'             {$$ = mk_ast_node(0, NULL, NULL);}

term:
    FOR idexpr IN bracket_op INTEGER ',' INTEGER ']' sum_op '(' expr ')'  {/*printf("");*/$$ = mk_ast_for_sum_node($2, $5, $7, $11);
                                $$->line_no=$4->line_no;
                                $$->line_no_2=$9->line_no;}
    | '(' expr ')'    {$$ = $2;/*printf("line no of id is %d", $$->line_no);*/}
    | INTEGER       {$$ = mk_ast_number_node($1);}
    | STRING        {$$ = mk_ast_string_node($1);}
    | ID            {$$ = mk_ast_symbol_reference_node($1);/*$$->line_no=yylineno;*//*printf("line no of id is %d", $$->line_no);*/}
    | BOOLEAN       {$$ = mk_ast_boolean_node($1);}
    //| NULL_VAL      {$$ = mk_ast_string_node("");}
    ;

bracket_op:
        '['             {$$ = mk_ast_node(0, NULL, NULL);}

sum_op:
        SUM             {$$ = mk_ast_node(0, NULL, NULL);}

idexpr:
        ID              {$$ = mk_ast_symbol_reference_node($1);
        $$->line_no=yylineno;
        /*printf("line no of id is %d", $$->line_no);*/}

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
    // block_level = 1;
    present_scope = (struct scope_node *)malloc(sizeof(struct scope_node));
    present_scope->parent = NULL;
    // present_scope->scope_level = 1;
    present_scope->len_child_scopes = 0;
    present_scope->len_symbol_table = 0;
    // printf("length child scopes present scope is %d\n", present_scope->len_child_scopes);
    typecheck(node);
    if (typeError == 0) {
        present_scope->current_child_scope = 0;
        // printf("traverse begin\n");
        traverse(node);
        // find_def_use(node);
    }
    

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

void printErrorMessage(int line) {
    typeError = 1;
    printf("Type violation in %d\n", line);
}

void actIfViolation(struct ast_node * ast_tree, struct ast_node * result, int typeViolationCheckLeft, int typeViolationCheckRight) {
    if (typeViolationCheckLeft == -1 || typeViolationCheckRight == -1) {
        result->node_type = 'U';
    } else if (typeViolationCheckLeft == 1 || typeViolationCheckRight == 1) {
        result->node_type = 'U';
        printErrorMessage(ast_tree->line_no);
        // printf("Type violation error in line %d\n", ast_tree->line_no);
    }
}



char * getOperandType(int node_type) {
    if (node_type == '+' || node_type == '-' || node_type == '*' || node_type == '<' || node_type == 'E'
        || node_type == 'w' || node_type == 'x' || node_type == 'y' || node_type == 'z')
        return "number";
    printf("undefined node type\n");
    return NULL;
}

void checkSymbolViolation(struct ast_node * dummy, struct scope_node *scope) {
    if (dummy->node_type == 's') {
        // struct ast_symbol_reference_node * node = (struct ast_symbol_reference_node *) dummy;
        struct ast_node * node = dummy;
        struct symbol_node * sym_node = lookup_variable_present_scope(present_scope, node->symbol->name);
        if (sym_node == NULL) {
            printErrorMessage(node->line_no);
            // printf("type violation error in line %d\n", node->line_no);
        }
    }
}


struct ast_node * typecheck(struct ast_node * ast_tree) {
    // printf("start ast tree %p\n", ast_tree);
    
    if (ast_tree == NULL) {
        // printf("null\n");
        return NULL;
    }
    // printf("yylineno is %d\n", yylineno);
    // printf("print node type %c line no %d\n", ast_tree->node_type, ast_tree->line_no);
    switch (ast_tree->node_type)
    {
        case 'Q':
        {
            struct ast_node * left = ast_tree->left;
            struct symbol_node * sym_node;
            if (left->node_type != 's') {
                typecheck(ast_tree->left);
            } else {
                int typeViolation = typeViolationCheck(present_scope, left, "", 's');
                if (typeViolation == -1) {
                    printErrorMessage(ast_tree->line_no);
                    // printf("Type violation error in line %d\n", ast_tree->line_no);
                }
                sym_node = lookup_variable_present_scope(present_scope, left->symbol->name);
            }
            break;
        }
        case 'q':
        {
            // printf("inside input list\n");
            struct ast_node * left = ast_tree->left;
            struct symbol_node * sym_node;
            if (left->node_type != 's') {
                typecheck(ast_tree->left);
            } else {
                int typeViolation = typeViolationCheck(present_scope, ast_tree, "", 's');
                if (typeViolation == -1) {
                    printErrorMessage(ast_tree->line_no);
                    // printf("Type violation error in line %d\n", ast_tree->line_no);
                }
                sym_node = lookup_variable_present_scope(present_scope, left->symbol->name);
            }
            // printf("%p", ast_tree->right);
            typecheck(ast_tree->right);
            sym_node = lookup_variable_present_scope(present_scope, ast_tree->right->symbol->name);
            break;
        }
        case 'l':
        {
            // printf("inside l block\n");
            struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
            result->node_type = 'n';
            struct ast_node * left = ast_tree->left;
            struct ast_node * dummy;
            // printf("left node type %c\n", left->node_type);
            if (left->node_type != 's') {
                dummy = typecheck(ast_tree->left);
            } else {
                dummy = left;
            }
            char * value1 = get_symbol_name(dummy);
            //printf("value 1 is %s\n", value1);
            // struct ast_node * dummy2 = typecheck(ast_tree->right);
            struct ast_node * right = ast_tree->right;
            // printf("right node type %c\n", right->node_type);
            struct ast_node * dummy2;
            if (right->node_type != 's') {
                dummy2 = typecheck(ast_tree->right);
            } else {
                dummy2 = right;
            }
            char * value2 = get_symbol_name(dummy2);
            // printf("%s\n", value2);
            //printf("value 2 is %s\n", value2);
            result->value = malloc(strlen(value1)+strlen(value2)+1);
            strcpy(result->value, value1);
            strcat(result->value, " ");
            strcat(result->value, value2);
            // printf("value is %s\n", result->value);
            return (struct ast_node *) result;
            break;
        }
        case 'i':
        case 'b':
        case 'c':
        {
            char * type;
            if (ast_tree->node_type == 'i') type = "number";
            else if (ast_tree->node_type == 'b') type = "boolean";
            else type = "string";
            // struct ast_node * dummy = typecheck(ast_tree->left);
            struct ast_node * left = ast_tree->left;
            struct ast_node * dummy;
            if (left->node_type != 's') {
                dummy = typecheck(ast_tree->left);
            } else {
                dummy = left;
            }
            char * value1 = get_symbol_name(dummy);
            char * variable = strtok(value1, " ");
            while (variable != NULL) {
                // printf("%s ", variable);
                int check = add_variable_to_present_scope(present_scope, variable, type);
                if (check == 0) {

                    printErrorMessage(ast_tree->line_no);
                    // printf("redeclaration error in line %d\n", ast_tree->line_no);
                } else {
                    setDeclareValue(present_scope, variable); 
                }
                variable = strtok(NULL, " ");
            }
            // printf("present scope length %d\n", present_scope->len_symbol_table);
            break;
        }
        case 'C':
        {
            // printf("inside compound statement\n");
            present_scope = create_new_scope(present_scope);
            typecheck(ast_tree->left);
            present_scope = present_scope->parent;
            break;

        }
        case '+':
        case '-':
        case '*':
        case '<':
        case 'E':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        {
            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            result->node_type = getOperatorResultNodeType(ast_tree->node_type);
            char * operand_type = getOperandType(ast_tree->node_type);

            struct ast_node * dummy = typecheck(ast_tree->left);
            // printf("before type check\n");
            int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, operand_type, 'N');
            // if (dummy->node_type == 's' && typeViolationCheckLeft == -1) {
            //     printf("type violation error in line %d\n", dummy->line_no);
            // }
            //result->value = add_value(dummy);
            struct ast_node * dummy2 = typecheck(ast_tree->right);
            int typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, operand_type, 'N');
            // if (dummy2->node_type == 's' && typeViolationCheckLeft == -1) {
            //     printf("type violation error in line %d\n", dummy->line_no);
            // }
            actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
            // printf("after type check\n");
            return (struct ast_node *) result;
            break;
        }
        case 'F':
        {
            struct ast_for_sum_node * for_node = (struct ast_for_sum_node *) ast_tree;
            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            result->node_type = 'N';
            present_scope = create_new_scope(present_scope);


            struct ast_node * symbol_node = for_node->symbol;
            int range1 = for_node->left_value;
            int range2 = for_node->right_value;
            char * variable = get_symbol_name(symbol_node);
            add_variable_to_present_scope(present_scope, variable, "number");

            // printf("ranges are %d %d\n", range1, range2);
            if (range1 > range2) {

                printErrorMessage(for_node->line_no);
                result->node_type = 'U';
                // printf("Type violation error in line %d\n", for_node->line_no);
            }
            struct ast_node * expression_node = typecheck(for_node->expression);
            int typeViolation = typeViolationCheck(present_scope, expression_node, "number", 'N');
            if (typeViolation != 0) {
                result->node_type = 'U';
                if (typeViolation == 1) {
                    printErrorMessage(for_node->line_no_2);
                    // printf("Type violation error in line %d\n", for_node->line_no);
                }

            }
            
            // struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
            // struct ast_number_node * condition = (struct ast_number_node *) traverse(while_node->condition);
            // while(condition->value != 0) {
            //     traverse(while_node->while_branch);
            //     condition = (struct ast_number_node *) traverse(while_node->condition);
            // }
            //printf("while block came");
            present_scope = present_scope->parent;
            return (struct ast_node *) result;
            break;
        }
        case 'a':
        {
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
            struct ast_node * dummy = typecheck(ast_tree->left);
            int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, "boolean", 'B');
            //result->value = add_value(dummy);
            struct ast_node * dummy2 = typecheck(ast_tree->right);
            int typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, "boolean", 'B');
            actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
            return (struct ast_node *) result;
            break;
        }
        case 's':
        {
            int typeViolation = typeViolationCheck(present_scope, ast_tree, "", 's');
            if (typeViolation == -1) {
                printErrorMessage(ast_tree->line_no);
                // printf("Type violation error in line %d\n", ast_tree->line_no);
            }
            break;
        }
        case 'O':
        {

            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            struct ast_node * dummy = typecheck(ast_tree->left);
            int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, "boolean", 'B');
            int typeViolationCheckRight = 0;
            if (typeViolationCheckLeft == 0) {
                struct ast_node * dummy2 = typecheck(ast_tree->right);
                typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, "boolean", 'B');
                actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
                if (result->node_type != 'U') {
                    result->node_type = 'B';
                }
            } else if (typeViolationCheckLeft == 1) {
                typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, "string", 'n');
                struct ast_node * dummy2 = typecheck(ast_tree->right);
                typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, "string", 'n');
                actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
                if (result->node_type != 'U') {
                    result->node_type = 'n';
                }
            } else {
                struct ast_node * dummy2 = typecheck(ast_tree->right);
                result->node_type = 'U';
            }
            return (struct ast_node *) result;
            break;        
        }

        case 'A':
        {
            // printf("inside assignment\n");
            struct ast_assignment_node * node = (struct ast_assignment_node *) ast_tree;
            //struct symbol_node * sym_node = find(node->symbol->name);
            // struct ast_symbol_reference_node * sym_ref_node = (struct ast_symbol_reference_node *) typecheck(node->symbol);
            struct ast_node * sym_ref_node = typecheck(node->symbol);
            struct symbol_node * sym_node = lookup_variable_present_scope(present_scope, sym_ref_node->symbol->name);
            // if (value_node->node_type == 's') {
            //     struct ast_symbol_reference_node * dum = (struct ast_symbol_reference_node *) value_node;
            //     printf("inside assignment type of right hand side is %d\n", dum->line_no);
            // }
            // printf("inside assignment type of right hand side is %d\n", value_node->line_no);
            // if (sym_node == NULL) {
            //     printf("type violation error in line %d\n", sym_ref_node->line_no);
            // } else {

            // }
            struct ast_node * value_node = typecheck(node->value);
            
            if (value_node->node_type == 'U') 
            {
            } 
            else if ( sym_node != NULL && (   ((value_node->node_type == 'N') && (strcmp(sym_node->type, "number")==0))
                || ((value_node->node_type == 'n') && (strcmp(sym_node->type, "string")==0))
                || ((value_node->node_type == 'B') && (strcmp(sym_node->type, "boolean")==0))
                    )
                )
            {

            } 
            else if (sym_node != NULL && value_node->node_type == 's')
            {
                int typeViolationCheckLeft = typeViolationCheck(present_scope, value_node, sym_node->type, 0);
                if (typeViolationCheckLeft == 1) {
                    // sym_node->type = "undefined";
                    printErrorMessage(ast_tree->line_no);
                    // printf("type violation error in line %d\n", ast_tree->line_no);
                } 
                // else if (typeViolationCheckLeft == -1) {
                //     printErrorMessage(value_node->line_no);
                //     // printf("type violation error in line %d\n", value_node->line_no);
                //     // sym_node->type = "undefined";
                // }
                
            }
            else if (sym_node != NULL && value_node->node_type != 'U') {
                printErrorMessage(ast_tree->line_no);
                // printf("type violation error in line %d\n", ast_tree->line_no);
            }
            //printf("end of assignment\n");
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
            typecheck(ast_tree->left);
            typecheck(ast_tree->right);
            break;
        case 'P':
        {
            struct ast_node * value_node = typecheck(ast_tree->left);
            // checkSymbolViolation(value_node, present_scope);
            break;
        }
            
        case 'p':
        {
            // printf("inside p block\n");
            struct ast_node * value_node = typecheck(ast_tree->left);
            // checkSymbolViolation(value_node, present_scope);
            break;
        }
            
        case 'L':
        {  
            // printf("inside L block\n");
            struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
            result->node_type = 'n';
            struct ast_node * dummy = typecheck(ast_tree->left);
            struct ast_node * dummy2 = typecheck(ast_tree->right);
            break;
        }
        case 'I':
        {
            struct ast_node * if_node = ast_tree;
            struct ast_node * condition = typecheck(if_node->condition);
            int typeViolation = typeViolationCheck(present_scope, condition, "boolean", 'B');
            // printf("before typeViolation check in if\n");
            if (typeViolation == 1) {
                printErrorMessage(ast_tree->line_no);
                // printf("type violation error in line %d\n", ast_tree->line_no);
            } else {
               
            }
            // printf("after typeViolation in if\n");
            typecheck(if_node->left);
            // // printf("after if branch in if\n");
            // if (if_node->right != NULL /*|| if_node->right != 0x2*/) {
            //     // printf("inside else\n");
                typecheck(if_node->right);
            // }
            
            // printf("after else branch in if\n");
            //printf("if block came");
            break;
        }
        case 'W':
        {
            // printf("line no of while %d\n", ast_tree->line_no);
            // struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
            struct ast_node * while_node = ast_tree;
            struct ast_node * condition = typecheck(while_node->condition);
            int typeViolation = typeViolationCheck(present_scope, condition, "boolean", 'B');
            if (typeViolation == 1) {
                printErrorMessage(ast_tree->line_no);
                // printf("type violation error in line %d\n", ast_tree->line_no);
            } else {
               
            }
            // while(condition->value != 0) {
            //     traverse(while_node->while_branch);
            //     condition = (struct ast_number_node *) traverse(while_node->condition);
            // }
            typecheck(while_node->left);
            //printf("while block came");
            break;
        }

            
    }
    return ast_tree;
}

