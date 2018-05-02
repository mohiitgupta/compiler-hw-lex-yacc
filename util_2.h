 // int isWhile = 0;

struct scope_node * create_new_scope(struct scope_node *scope) {
    struct scope_node * new_scope = (struct scope_node *)malloc(sizeof(struct scope_node));
    new_scope->parent = scope;
    new_scope->len_symbol_table = 0;
    new_scope->len_child_scopes = 0;
    
    int childIndex = scope->len_child_scopes;
    scope->child_scopes[childIndex] = new_scope;
    scope->len_child_scopes = childIndex+1;
    return new_scope;
}

int add_variable_to_present_scope(struct scope_node *scope, char * symbol_name, char * type) {
    // printf("present scope length %d\n", scope->len_symbol_table);
    for (int i=0; i < scope->len_symbol_table; i++) {
        if (strcmp(scope->symbols[i]->name, symbol_name) == 0) {
            return 0;
        }
    }
    struct symbol_node * node = create_symbol(symbol_name);
    node->type = type;
    scope->symbols[scope->len_symbol_table++] = node;

    return 1;
}

void setDeclareValue(struct scope_node *scope, char * symbol_name) {
    for (int i=0; i < scope->len_symbol_table; i++) {
        if (strcmp(scope->symbols[i]->name, symbol_name) == 0) {
            scope->symbols[i]->declare = "true";
        }
    }
}

struct symbol_node * find_variable_scope(char * symbol_name) {
    struct scope_node *scope = present_scope;
    // printf("present scope length %d\n", scope->len_symbol_table);
    for (int i=0; i < scope->len_symbol_table; i++) {
        if (strcmp(scope->symbols[i]->name, symbol_name) == 0) {
            return scope->symbols[i];
        }
    }
    // struct symbol_node * node = create_symbol(symbol_name);
    // node->type = type;
    // scope->symbols[scope->len_symbol_table++] = node;

    return NULL;
}

struct symbol_node * lookup_variable_present_scope(struct scope_node *scope, char * symbol_name) {
    for (int i=0; i < scope->len_symbol_table; i++) {
        if (strcmp(scope->symbols[i]->name, symbol_name) == 0) {
            // if (strcmp(scope->symbols[i]->type, type) == 0) {
            //     return scope->symbols[i];
            // }
            // return 0;
            return scope->symbols[i];
        }
    }
    //int check = -1;
    struct symbol_node * node = NULL;
    if (scope->parent != NULL) {
        node = lookup_variable_present_scope(scope->parent, symbol_name);
        if (node != NULL) {
            add_variable_to_present_scope(scope, node->name, node->type);
        }
    }
    return node;
}



struct symbol_node * lookup_value_variable_present_scope(struct scope_node *scope, char * symbol_name) {
    for (int i=0; i < scope->len_symbol_table; i++) {
        if (strcmp(scope->symbols[i]->name, symbol_name) == 0) {
            struct symbol_node * variable = scope->symbols[i];
            if (variable->declare != NULL || variable->value != NULL) {
                //do nothing
            }
            else {
                struct scope_node * dummy_scope = scope;
                scope = scope->parent;
                struct symbol_node * parent_symbol = lookup_value_variable_present_scope(scope, variable->name);
                scope = dummy_scope;
                variable->value = parent_symbol->value;
            }
            // if (strcmp(scope->symbols[i]->type, type) == 0) {
            //     return scope->symbols[i];
            // }
            // return 0;
            return scope->symbols[i];
        }
    }
    //int check = -1;
    struct symbol_node * node = NULL;
    if (scope->parent != NULL) {
        node = lookup_variable_present_scope(scope->parent, symbol_name);
        if (node != NULL) {
            add_variable_to_present_scope(scope, node->name, node->type);
        }
    }
    return node;
}

int typeViolationCheck(struct scope_node *scope, struct ast_node * dummy, char * valid_type, int correct_type) {
    int typeViolationCode = 1;
    if (dummy->node_type == 's') {
        struct ast_symbol_reference_node * symbol_node = (struct ast_symbol_reference_node *) dummy;
        struct symbol_node * left_node = lookup_variable_present_scope(scope, symbol_node->symbol->name);
        if (left_node != NULL) {
            if (strcmp(left_node->type, valid_type) == 0) {
                typeViolationCode = 0;
            } else if (strcmp(left_node->type, "undefined") == 0) {
                typeViolationCode = -1;
            }
        } else {
            typeViolationCode = -1;
        }
    } 
    else if (dummy->node_type == correct_type) {
        typeViolationCode = 0;
    } 
    else if (dummy->node_type == 'U') {
        typeViolationCode = -1;
    }
    return typeViolationCode;
}


void setVariableParentScope(struct scope_node *scope, struct symbol_node * symbol) {
    for (int i=0; i < scope->len_symbol_table; i++) {
        if (strcmp(scope->symbols[i]->name, symbol->name) == 0) {
            // if (strcmp(scope->symbols[i]->type, type) == 0) {
            //     return scope->symbols[i];
            // }
            // return 0;
            struct symbol_node * variable = scope->symbols[i];
            variable->value = symbol->value;
            if (variable->declare == NULL) {
                setVariableParentScope(scope->parent, variable);
            }
            // return scope->symbols[i];
        }
    }
}
void setValuesNonDeclaredVariables(struct scope_node *scope) {
    for (int i=0; i < scope->len_symbol_table; i++) {
        // if (strcmp(scope->symbols[i]->name, symbol_name) == 0) {
            // struct symbol_node * variable = scope->symbols[i];
            // for (int j=0; j < scope->len_child_scopes; j++) {
            //     struct scope_node * child_scope = scope->child_scopes[j];
            //     for (int k=0; k < child_scope->len_symbol_table; k++) {
            //         struct symbol_node * child_variable = child_scope->symbols[k];
            //         if ((strcmp(child_variable->name, variable->name) == 0) && (child_variable->declare == NULL)) {
            //             child_variable->value = variable->value;
            //         }
            //     }
            // }
            if (variable->declare != NULL) {
                //do nothing
            }
            else if (variable->value != NULL) {
                // struct scope_node * dummy_scope = scope;
                // scope = scope->parent;
                // struct symbol_node * parent_symbol = lookup_value_variable_present_scope(scope, variable->name);
                // scope = dummy_scope;
                // variable->value = parent_symbol->value;
                setVariableParentScope(scope->parent, variable);
            }
            // if (strcmp(scope->symbols[i]->type, type) == 0) {
            //     return scope->symbols[i];
            // }
            // return 0;
            // return scope->symbols[i];
        // }
    }
}

int add_value(struct ast_node * value_node) {
    if (value_node->node_type == 's') {
        struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        struct symbol_node * result = lookup_value_variable_present_scope(present_scope, left->symbol->name);
        /*if (strcmp(result->initialize, "initialized") == 0) {
            return result->value;
        } else {
            printf("not initialized\n");
        }*/
        if (result->value == NULL) {
            printf("Uninitialized variable in %d\n", left->line_no);
            exit(0);
        }
        int value = 0;
        if (strcmp(result->type, "number") == 0) {
            value = (int) *(int *)result->value; 
        } else if (strcmp(result->type, "boolean") == 0) {
            value = (int) *(int *)result->value; 
        } //else if (strcmp(result->type, "boolean") == 0)
        
        return value;
    } else if (value_node->node_type == 'N') {
        struct ast_number_node * left = (struct ast_number_node *) value_node;
        return left->value;
    } else if (value_node->node_type == 'B') {
        struct ast_boolean_node * left = (struct ast_boolean_node *) value_node;
        return left->value;
    } 
    // else if (value_node->node_type == 'n') {
    //     struct ast_string_node * left = (struct ast_string_node *) value_node;
    //     return left->value;
    // }
    return 0;
}

char * get_symbol_name(struct ast_node * value_node) {
    char *snum;
    // printf("inside get symbol name block node type is %c\n", value_node->node_type);
    if (value_node->node_type == 's') {
        //struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        //struct symbol_node * result = left->symbol;
        //printf("inside symbole reference block in get value\n");
        struct ast_symbol_reference_node * value_symbol_node = (struct ast_symbol_reference_node *) value_node;
        
        //struct symbol_node * result = find(value_symbol_node->symbol->name);
        // if (result->type == NULL) {
        //     printf("Uninitialized variable in %d\n", result->line);
        //     exit(0);
        // }
        // //printf("name of symbol is %s", result->name);
        // if (strcmp(result->type, "number") == 0) {
        //     snum = (char *)malloc(100);
        //     int number_dummy = *(int *)result->value;
        //     //printf("value of %s is %d\n", result->name, number_dummy);
        //     snprintf(snum, 100, "%d", number_dummy);
        //     //itoa(number_dummy,snum,10);
        // } else if (strcmp(result->type, "string") == 0){
        //     //snum = (char *) malloc(strlen(result->value)+1);
        //     //strcpy(snum, result->value);
        //     snum = (char *)result->value;
        // } else {
        //     printf("not initialized");
        // }
        //return snum;
        snum = value_symbol_node->symbol->name;
    } else if (value_node->node_type == 'n') {
        struct ast_string_node * left = (struct ast_string_node *) value_node;
        //fprintf(stderr, "size of string is %lu\n", strlen(left->value));
        //snum = (char *)malloc(strlen(left->value)+1);
        //strcpy(snum, left->value);
        //return left->value;

        snum = (char *)left->value;
    } else {
        printf("invalid type\n");
    }
    // int len = strlen(snum);
    // snum[len]='\0';
    //fflush(stdin);
    //printf("value of snum is %s\n", snum);
    return snum;
}
char * get_value(struct ast_node * value_node) {
    char *snum;
    //printf("inside get value block \n");
    if (value_node->node_type == 's') {
        //struct ast_symbol_reference_node * left = (struct ast_symbol_reference_node *) value_node;
        //struct symbol_node * result = left->symbol;
        //printf("inside symbole reference block in get value\n");
        struct ast_symbol_reference_node * value_symbol_node = (struct ast_symbol_reference_node *) value_node;
        
        struct symbol_node * result = lookup_value_variable_present_scope(present_scope, value_symbol_node->symbol->name);
        if (result->value == NULL) {
            printf("Uninitialized variable in %d\n", value_symbol_node->line_no);
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
            //snum = (char *) malloc(strlen(result->value)+1);
            //strcpy(snum, result->value);
            snum = (char *)result->value;
        } else if (strcmp(result->type, "boolean") == 0) {
            snum = (char *)malloc(100);
            int number_dummy = *(int *)result->value;
            //printf("value of %s is %d\n", result->name, number_dummy);
            if (number_dummy == 0) {
                snum = "false";
            } else if (number_dummy == 1) {
                snum = "true";
            }
            // snprintf(snum, 100, "%d", number_dummy);
            //itoa(number_dummy,snum,10);
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
        //snum = (char *)malloc(strlen(left->value)+1);
        //strcpy(snum, left->value);
        //return left->value;

        snum = (char *)left->value;
    } else if (value_node->node_type == 'B') {
        struct ast_boolean_node * left = (struct ast_boolean_node *) value_node;
        //fprintf(stderr, "size of string is %lu\n", strlen(left->value));
        //snum = (char *)malloc(strlen(left->value)+1);
        //strcpy(snum, left->value);
        //return left->value;
        if (left->value == 0) {
            snum = "false";
        } else if (left->value == 1) {
            snum = "true";
        }
        // snum = (char *)left->value;
    }
    // int len = strlen(snum);
    // snum[len]='\0';
    //fflush(stdin);
    //printf("value of snum is %s\n", snum);
    return snum;
}


struct ast_node * traverse(struct ast_node * ast_tree) {
    
    // printf("ast tree node type %c\n", ast_tree->node_type);
    // printf("present scope length %d\n", present_scope->len_symbol_table);
    // for (int i=0; i < present_scope->len_symbol_table; i++) {
    //     printf("%s ", present_scope->symbols[i]->name);
    //     if (present_scope->symbols[i]->value != NULL ) {
    //         int * number = ((int *)present_scope->symbols[i]->value);
    //         printf("%d ", *number);
    //     }
        
    //     printf("%s ", present_scope->symbols[i]->type);
    //     //printf("%s ", symbols[i]->string_val);
    //     printf("\n");
    // }
    if (ast_tree == NULL) {
        return NULL;
    }
    switch (ast_tree->node_type)
    {
        case 'C':
        {
            // printf("inside compound statement\n");
            
            int childIndex = present_scope->current_child_scope;
            // printf("child index is %d\n", childIndex);
            present_scope = present_scope->child_scopes[childIndex];
            present_scope->current_child_scope = 0;
            // printf("before traverse compound statement\n");
            traverse(ast_tree->left);

            setValuesNonDeclaredVariables(present_scope);
            present_scope = present_scope->parent;
            // if (isWhile == 0) {
                childIndex += 1;
                
            // }
            present_scope->current_child_scope = childIndex;
            // printf("child index at end is %d", childIndex);
            
            
            // printf("outside compound statement\n");
            break;

        }
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
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
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
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
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
        case 'w':
        {
            //printf("equality block came\n");
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) != result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }
        case 'x':
        {
            //printf("equality block came\n");
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) < result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }
        case 'y':
        {
            //printf("equality block came\n");
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) <= result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            return (struct ast_node *) result;
            break;
        }
        case 'z':
        {
            //printf("equality block came\n");
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
            struct ast_node * dummy = traverse(ast_tree->left);
            result->value = add_value(dummy);
            dummy = traverse(ast_tree->right);
            if (add_value(dummy) >= result->value) {
                result->value = 1;
            } else {
                result->value = 0;
            }
            //printf("result value is %d",result->value);
            return (struct ast_node *) result;
            break;
        }
        case 'a':
        {
            //printf("and block came\n");
            struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            result->node_type = 'B';
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
            // struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
            // result->node_type = 'B';
            struct ast_node * dummy = traverse(ast_tree->left);
            struct ast_symbol_reference_node * value_symbol_node;
            struct symbol_node * dum_ref;
            if (dummy->node_type == 's') {
                value_symbol_node = (struct ast_symbol_reference_node *) dummy;
                dum_ref = lookup_value_variable_present_scope(present_scope, value_symbol_node->symbol->name);
            }

            if (dummy->node_type == 'n'
                || ((dummy->node_type == 's' )&&(strcmp(dum_ref->type, "string")==0)))
            {
                struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
                result->node_type = 'n';
                char * value1 = get_value(dummy);
                struct ast_node * dummy2 = traverse(ast_tree->right);
                char * value2 = get_value(dummy2);
                result->value = malloc(strlen(value1)+strlen(value2)+1);
                strcpy(result->value, value1);
                strcat(result->value, value2);

                return (struct ast_node *) result;


            } else {
                struct ast_boolean_node * result = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
                result->node_type = 'B';
                result->value = add_value(dummy);
                dummy = traverse(ast_tree->right);
                if (add_value(dummy) || result->value) {
                    result->value = 1;
                } else {
                    result->value = 0;
                }
                return (struct ast_node *) result;

            }


            // result->value = add_value(dummy);
            // dummy = traverse(ast_tree->right);
            // if (add_value(dummy) || result->value) {
            //     result->value = 1;
            // } else {
            //     result->value = 0;
            // }
            // return (struct ast_node *) result;
            break;
        }

        case 'A':
        {
            struct ast_assignment_node * node = (struct ast_assignment_node *) ast_tree;
            struct ast_symbol_reference_node * ref_node = (struct ast_symbol_reference_node *) node->symbol;
            struct symbol_node * dummy = (struct symbol_node *) ref_node->symbol;
            struct symbol_node * sym_node = find_variable_scope(dummy->name);
            struct ast_node * value_node = traverse(node->value);
            if (value_node->node_type == 'N') 
            {
                struct ast_number_node * result = (struct ast_number_node *) value_node;
                int * number_dummy = (int*)malloc(sizeof(int));
                *number_dummy = result->value;
                // printf("value of result is %d\n", result->value);

                sym_node->value = (void *) number_dummy;
                // sym_node->type = "number";
                //printf("value stored in assignment is %d\n", *(int *)sym_node->value);

                //printf("");
                //sym_node->initialize = "initialized";
            } else if (value_node->node_type == 'B') 
            {
                struct ast_boolean_node * result = (struct ast_boolean_node *) value_node;
                int * number_dummy = (int*)malloc(sizeof(int));
                *number_dummy = result->value;

                sym_node->value = (void *) number_dummy;
                // sym_node->type = "boolean";
                //printf("value stored in assignment is %d\n", *(int *)sym_node->value);

                //printf("");
                //sym_node->initialize = "initialized";
            }
             else if (value_node->node_type == 'n')
            {
                struct ast_string_node * result = (struct ast_string_node *) value_node;
                //char * string_dummy = result->value;
                sym_node->value = (char *) malloc(strlen(result->value)+1);
                strcpy(sym_node->value, result->value);
                //printf("value of string is %s, %s, %lu", result->value, sym_node->value, strlen(result->value));
                //sym_node->value = (void *) string_dummy;
                // sym_node->type = "string";
                //sym_node->initialize = "initialized";
            } else if (value_node->node_type == 's')
            {
                struct ast_symbol_reference_node * result_sym_node = (struct ast_symbol_reference_node *) value_node;
                struct symbol_node * result = find_variable_scope(result_sym_node->symbol->name);

                if (result->value == NULL) {
                    fprintf(stderr, "Uninitialized variable in %d\n", result_sym_node->line_no);
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
                    //printf("value of string is %s, %s", result->value, sym_node->value);
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
            // printf("string value is %s", string_value);
            if (strlen(string_value) != 0) {
                fprintf(stderr, "%s \n", string_value); 
            } else {
                //fflush(stdin);
                fprintf(stderr, "\n"); 
            }
            break;
        }
            
        case 'p':
        {
            struct ast_node * value_node = traverse(ast_tree->left);
            char * string_value = get_value(value_node);
            if (strlen(string_value) != 0) {
                fprintf(stderr, "%s", string_value);
            }
            
            //free(string_value);
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
            result->value = malloc(strlen(value1)+strlen(value2)+2);
            strcpy(result->value, value1);
            strcat(result->value, " ");
            strcat(result->value, value2);
            // printf("value is %s", result->value);
            return (struct ast_node *) result;
            break;
        }
        case 'I':
        {
            struct ast_node * if_node = (struct ast_node *) ast_tree;
            int condition_value = 0;
            // struct ast_boolean_node * condition = (struct ast_boolean_node *) traverse(if_node->condition);
            // if (condition->node_type == 's') {
            //     struct ast_symbol_reference_node * result_sym_node = (struct ast_symbol_reference_node *) condition;
            //     struct symbol_node * result = find_variable_scope(result_sym_node->symbol->name);

            //     if (result->value == NULL) {
            //         fprintf(stderr, "Uninitialized variable in %d\n", result_sym_node->line_no);
            //         exit(0);
            //     }
            //     condition_value = (int) result->value;
            //     // }
            // } else {
            //     condition_value = condition->value;
            // }
            condition_value = add_value(traverse(if_node->condition));
            if (condition_value == 0) {
                present_scope->current_child_scope++;
                // printf("if test3 conditon value is %d\n",condition_value);
                traverse(if_node->right);
            } else {
                // printf("if test2 conditon value is %d\n",condition_value);
                traverse(if_node->left);
            }
            //printf("if block came");
            break;
        }
        case 'W':
        {
            // isWhile = 1;
            struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
            // struct ast_boolean_node * condition = (struct ast_boolean_node *) traverse(while_node->condition);
            int condition_value = add_value(traverse(while_node->condition));
            int initial_track = 1;
            while(condition_value != 0) {
                if (initial_track == 0) {
                    int childIndex = present_scope->current_child_scope;
                    present_scope->current_child_scope = childIndex-1;
                }
                traverse(while_node->while_branch);
                condition_value = add_value(traverse(while_node->condition));
                //printf("condition value is %d\n", condition_value);
                // condition = (struct ast_boolean_node *) traverse(while_node->condition);
                initial_track = 0;
            }
            // isWhile = 0;
            // int childIndex = present_scope->current_child_scope;
            // present_scope->current_child_scope = childIndex+1;
            //printf("while block came");
            break;
        }
        case 'F':
        {
            struct ast_for_sum_node * for_node = (struct ast_for_sum_node *) ast_tree;
            struct ast_number_node * result = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
            result->node_type = 'N';
            // struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            // result->node_type = 'N';
            // present_scope = create_new_scope(present_scope);
            int childIndex = present_scope->current_child_scope;
            //printf("child index is %d\n", childIndex);
            // printf("child scopes index %d\n", childIndex);
            present_scope = present_scope->child_scopes[childIndex];
            present_scope->current_child_scope = 0;


            struct ast_node * symbol_node = for_node->symbol;
            int range1 = for_node->left_value;
            int range2 = for_node->right_value;
            char * variable_name = get_symbol_name(symbol_node);
            //printf("variable name is %s \n", variable_name);
            struct symbol_node * sym_node = find_variable_scope(variable_name);

            int * number_dummy = (int*)malloc(sizeof(int));
            *number_dummy = range1;
            sym_node->value = (void *) number_dummy;
            int value = 0;

            for (int i=range1; i <= range2; i++) {
                *number_dummy = i;
                sym_node->value = (void *) number_dummy;
                value += add_value(traverse(for_node->expression));
                // printf("value is %d\n", value);
            }

            // add_variable_to_present_scope(present_scope, variable, "number");
            result->value = value;

            present_scope = present_scope->parent;
            present_scope->current_child_scope = childIndex;
            return (struct ast_node *) result;
            break;
        }
            
    }
    return ast_tree;
}