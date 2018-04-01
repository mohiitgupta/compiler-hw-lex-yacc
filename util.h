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
            //snum = (char *) malloc(strlen(result->value)+1);
            //strcpy(snum, result->value);
            snum = (char *)result->value;
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
        //snum = (char *)malloc(strlen(left->value)+1);
        //strcpy(snum, left->value);
        //return left->value;

        snum = (char *)left->value;
    }
    // int len = strlen(snum);
    // snum[len]='\0';
    //fflush(stdin);
    //printf("value of snum is %s\n", snum);
    return snum;
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
                //printf("value of string is %s, %s, %lu", result->value, sym_node->value, strlen(result->value));
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
            //printf("string length is %lu", strlen(string_value));
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