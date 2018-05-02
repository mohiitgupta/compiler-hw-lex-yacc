int getOperatorResultNodeType(int node_type) {
    if (node_type == '+' || node_type == '-' || node_type == '*')
        return 'N';
    else if (node_type == '<' || node_type == 'E' || node_type == 'w' || node_type == 'x' || node_type == 'y' || node_type == 'z')
        return 'B';
    //printf("undefined node type\n");
    return 0;
}

void update_use_set(struct ast_node * parent, struct ast_node * child) {
    if (child->node_type != 's') {
        //printf("child use length is %d\n", child->use_length);
        for (int i=0; i < child->use_length; i++) {
            parent->use[parent->use_length++] = child->use[i];
        }
    } else {
        // struct ast_symbol_reference_node * dummy_reference = (struct ast_symbol_reference_node *) child;
        struct ast_node * dummy_reference = child;
        parent->use[parent->use_length++] = dummy_reference->symbol->name;
    }
    // for (int i=0; i < parent->use_length; i++) {
    //     printf("use element for node %c index %d is %s\n", parent->node_type, i, parent->use[i]);
    // }
}
void update_def_set(struct ast_node * parent, struct ast_node * child) {
    if (child->node_type != 's') {
        for (int i=0; i < child->def_length; i++) {
            parent->def[parent->def_length++] = child->def[i];
        }
    } else {
        // struct ast_symbol_reference_node * dummy_reference = (struct ast_symbol_reference_node *) child;
        struct ast_node * dummy_reference = child;
        parent->def[parent->def_length++] = dummy_reference->symbol->name;
    }
    // for (int i=0; i < parent->use_length; i++) {
    //     printf("use element for node %c index %d is %s\n", parent->node_type, i, parent->use[i]);
    // }
}

void update_assignment_use_set(struct ast_assignment_node * parent, struct ast_node * child) {
    if (child->node_type != 's') {
        for (int i=0; i < child->use_length; i++) {
            parent->use[parent->use_length++] = child->use[i];
        }
    } else {
        // struct ast_symbol_reference_node * dummy_reference = (struct ast_symbol_reference_node *) child;
        struct ast_node * dummy_reference = child;
        parent->use[parent->use_length++] = dummy_reference->symbol->name;
    }
    // for (int i=0; i < parent->use_length; i++) {
    //     printf("use element for node %c index %d is %s\n", parent->node_type, i, parent->use[i]);
    // }
}

void update_assignment_def_set(struct ast_assignment_node * assignment_parent, char * symbol_name) {

    if (assignment_parent->node_type == 'A') {
        // struct ast_assignment_node * assignment_parent = (struct ast_assignment_node *)parent;
        // printf("symbol def is %s\n", symbol_name);
        assignment_parent->def[assignment_parent->def_length++] = symbol_name;
        // for (int i=0; i < assignment_parent->def_length; i++) {
        //     printf("def element %d is %s\n", i, assignment_parent->def[i]);
        // }
    }
    // else {
    //     // printf("symbol def is %s\n", symbol_name);
    //     parent->def[parent->def_length++] = symbol_name;
    //     // for (int i=0; i < parent->def_length; i++) {
    //     //     printf("def element %d is %s\n", i, parent->def[i]);
    //     // }
    // }
}

void printUseSetDebug(struct ast_node * node) {
    // printf("use set for node %c is given below:\n", node->node_type);
    // for (int i=0; i < node->use_length; i++) {
    //     printf("%s\n",node->use[i]);
    // }
}


struct ast_node * find_def_use(struct ast_node * ast_tree) {
    if (ast_tree == NULL) {
        // printf("null\n");
        return NULL;
    }
    // printf("yylineno is %d\n", yylineno);
    // printf("print node type %c line no %d\n", ast_tree->node_type, ast_tree->line_no);
    switch (ast_tree->node_type)
    {
        case 'S':
        {
            find_def_use(ast_tree->left);
            find_def_use(ast_tree->right);
            break;
        }
        case 'C':
        {
            // printf("inside compound statement\n");
            // present_scope = create_new_scope(present_scope);
            find_def_use(ast_tree->left);
            // present_scope = present_scope->parent;
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
        case 'a':
        case 'O':
        {
            // printf("inside operator one\n");
            struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
            result->node_type = getOperatorResultNodeType(ast_tree->node_type);
            // char * operand_type = getOperandType(ast_tree->node_type);

            struct ast_node * dummy = find_def_use(ast_tree->left);
            update_use_set(result, dummy);
            // printf("before type check\n");
            // int typeViolationCheckLeft = typeViolationCheck(present_scope, dummy, operand_type, 'N');
            // if (dummy->node_type == 's' && typeViolationCheckLeft == -1) {
            //     printf("type violation error in line %d\n", dummy->line_no);
            // }
            //result->value = add_value(dummy);
            struct ast_node * dummy2 = find_def_use(ast_tree->right);
            update_use_set(result, dummy2);
            // int typeViolationCheckRight = typeViolationCheck(present_scope, dummy2, operand_type, 'N');
            // if (dummy2->node_type == 's' && typeViolationCheckLeft == -1) {
            //     printf("type violation error in line %d\n", dummy->line_no);
            // }
            // actIfViolation( ast_tree, (struct ast_node *) result, typeViolationCheckLeft, typeViolationCheckRight);
            // printf("after type check\n");
            printUseSetDebug(result);
            return (struct ast_node *) result;
            break;
        }
         case 'A':
        {
            // printf("inside assignment\n");
            struct ast_assignment_node * node = (struct ast_assignment_node *) ast_tree;
            //struct symbol_node * sym_node = find(node->symbol->name);
            // struct ast_symbol_reference_node * sym_ref_node = (struct ast_symbol_reference_node *) find_def_use(node->symbol);
            struct ast_node * sym_ref_node = find_def_use(node->symbol);
            struct symbol_node * sym_node = lookup_variable_present_scope(present_scope, sym_ref_node->symbol->name);
            struct ast_node * value_node = find_def_use(node->value);
            update_assignment_def_set(node, sym_ref_node->symbol->name);
            // printf("length of def set of node is %d\n", node->def_length);
            // printf("def set for node %c is given below:\n", node->node_type);
            // for (int i=0; i < node->def_length; i++) {
            //     printf("%s\n",node->def[i]);
            // }

            update_assignment_use_set(node, value_node);
            // printf("use set for node %c is given below:\n", node->node_type);
            // for (int i=0; i < node->use_length; i++) {
            //     printf("%s\n",node->use[i]);
            // }
            break;
            
        }
        case 'Q':
        {
            struct ast_node * left = ast_tree->left;
            if (left->node_type != 's') {
                find_def_use(left);
                update_def_set(ast_tree, left);
            } else {
                update_def_set(ast_tree, left);
            }
            
            break;
        }
        case 'q':
        {
            // printf("inside input list\n");
            struct ast_node * left = ast_tree->left;
            if (left->node_type != 's') {
                find_def_use(left);
                update_def_set(ast_tree, left);
            } else {
                update_def_set(ast_tree, left);
            }
            // printf("%p", ast_tree->right);
            update_def_set(ast_tree, ast_tree->right);
            // printf("def set for node %c is given below:\n", ast_tree->node_type);
            // for (int i=0; i < ast_tree->def_length; i++) {
            //     printf("%s\n",ast_tree->def[i]);
            // }
            break;
        }
        case 'L':
        {
            // printf("inside input list\n");
            if (ast_tree->left->node_type != 's') {
                struct ast_node * left = find_def_use(ast_tree->left);
                update_use_set(ast_tree, left);
            } else {
                update_use_set(ast_tree, ast_tree->left);
            }
            if (ast_tree->right->node_type != 's') {
                struct ast_node * right = find_def_use(ast_tree->right);
                // printUseSetDebug(right);
                update_use_set(ast_tree, right);
            } else {
                update_use_set(ast_tree, ast_tree->right);
            }
            // printUseSetDebug(ast_tree);
            // printf("%p", ast_tree->right);
            // printf("def set for node %c is given below:\n", ast_tree->node_type);
            // for (int i=0; i < ast_tree->def_length; i++) {
            //     printf("%s\n",ast_tree->def[i]);
            // }
            break;
        }
        case 'P':
        case 'p':
        {
            struct ast_node * value_node = find_def_use(ast_tree->left);
            // printUseSetDebug(value_node);
            update_use_set(ast_tree, value_node);
            printUseSetDebug(ast_tree);
            // checkSymbolViolation(value_node, present_scope);
            break;
        }
        case 'I':
        {
            // printf("inside if\n");
            struct ast_node * value_node = find_def_use(ast_tree->condition);
            // printf("inside if second\n");
            // printUseSetDebug(value_node);
            update_use_set(ast_tree, value_node);
            find_def_use(ast_tree->left);
            find_def_use(ast_tree->right);
            printUseSetDebug(ast_tree);
            break;
        }
        case 'W':
        {
            // printf("inside while\n");
            struct ast_node * value_node = find_def_use(ast_tree->condition);
            // printf("inside if second\n");
            // printUseSetDebug(value_node);
            update_use_set(ast_tree, value_node);
            find_def_use(ast_tree->left);
            printUseSetDebug(ast_tree);
            break;
        }
        case 'F':
        {
            // printf("inside while\n");
            struct ast_for_sum_node * for_node = (struct ast_for_sum_node *) ast_tree;
            struct ast_node * symbol_node = for_node->symbol;
            char * variable = get_symbol_name(symbol_node);
            for_node->def[for_node->def_length++] = variable;
            // printf("inside if second\n");
            // printUseSetDebug(value_node);

            find_def_use(for_node->expression);
            printUseSetDebug(ast_tree);

            // printf("def set for node %c is given below:\n", ast_tree->node_type);
            // for (int i=0; i < ast_tree->def_length; i++) {
            //     printf("%s\n",ast_tree->def[i]);
            // }
            break;
        }
        // case 'l':
        // {
        //     // printf("inside l block\n");
        //     struct ast_string_node * result = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
        //     result->node_type = 'n';
        //     struct ast_node * left = ast_tree->left;
        //     struct ast_node * dummy;
        //     // printf("left node type %c\n", left->node_type);
        //     if (left->node_type != 's') {
        //         dummy = typecheck(ast_tree->left);
        //     } else {
        //         dummy = left;
        //     }
        //     char * value1 = get_symbol_name(dummy);
        //     //printf("value 1 is %s\n", value1);
        //     // struct ast_node * dummy2 = typecheck(ast_tree->right);
        //     struct ast_node * right = ast_tree->right;
        //     // printf("right node type %c\n", right->node_type);
        //     struct ast_node * dummy2;
        //     if (right->node_type != 's') {
        //         dummy2 = typecheck(ast_tree->right);
        //     } else {
        //         dummy2 = right;
        //     }
        //     char * value2 = get_symbol_name(dummy2);
        //     // printf("%s\n", value2);
        //     //printf("value 2 is %s\n", value2);
        //     result->value = malloc(strlen(value1)+strlen(value2)+1);
        //     strcpy(result->value, value1);
        //     strcat(result->value, " ");
        //     strcat(result->value, value2);
        //     // printf("value is %s\n", result->value);
        //     return (struct ast_node *) result;
        //     break;
        // }
        // case 'i':
        // case 'b':
        // case 'c':
        // {
        //     char * type;
        //     if (ast_tree->node_type == 'i') type = "number";
        //     else if (ast_tree->node_type == 'b') type = "boolean";
        //     else type = "string";
        //     // struct ast_node * dummy = typecheck(ast_tree->left);
        //     struct ast_node * left = ast_tree->left;
        //     struct ast_node * dummy;
        //     if (left->node_type != 's') {
        //         dummy = typecheck(ast_tree->left);
        //     } else {
        //         dummy = left;
        //     }
        //     char * value1 = get_symbol_name(dummy);
        //     char * variable = strtok(value1, " ");
        //     while (variable != NULL) {
        //         // printf("%s ", variable);
        //         int check = add_variable_to_present_scope(present_scope, variable, type);
        //         if (check == 0) {

        //             printErrorMessage(ast_tree->line_no);
        //             // printf("redeclaration error in line %d\n", ast_tree->line_no);
        //         } else {
        //             setDeclareValue(present_scope, variable); 
        //         }
        //         variable = strtok(NULL, " ");
        //     }
        //     // printf("present scope length %d\n", present_scope->len_symbol_table);
        //     break;
        // }
        
        
        // case 'F':
        // {
        //     struct ast_for_sum_node * for_node = (struct ast_for_sum_node *) ast_tree;
        //     struct ast_node * result = (struct ast_node *) malloc (sizeof (struct ast_node));
        //     result->node_type = 'N';
        //     present_scope = create_new_scope(present_scope);


        //     struct ast_node * symbol_node = for_node->symbol;
        //     int range1 = for_node->left_value;
        //     int range2 = for_node->right_value;
        //     char * variable = get_symbol_name(symbol_node);
        //     add_variable_to_present_scope(present_scope, variable, "number");


        //     if (range1 > range2) {
        //         printErrorMessage(for_node->line_no);
        //         result->node_type = 'U';
        //         // printf("Type violation error in line %d\n", for_node->line_no);
        //     }
        //     struct ast_node * expression_node = typecheck(for_node->expression);
        //     int typeViolation = typeViolationCheck(present_scope, expression_node, "number", 'N');
        //     if (typeViolation != 0) {
        //         result->node_type = 'U';
        //         if (typeViolation == 1) {
        //             printErrorMessage(for_node->line_no_2);
        //             // printf("Type violation error in line %d\n", for_node->line_no);
        //         }

        //     }
            
        //     // struct ast_while_node * while_node = (struct ast_while_node *) ast_tree;
        //     // struct ast_number_node * condition = (struct ast_number_node *) traverse(while_node->condition);
        //     // while(condition->value != 0) {
        //     //     traverse(while_node->while_branch);
        //     //     condition = (struct ast_number_node *) traverse(while_node->condition);
        //     // }
        //     //printf("while block came");
        //     present_scope = present_scope->parent;
        //     return (struct ast_node *) result;
        //     break;
        // }
       
        // case 's':
        // {
        //     // int typeViolation = typeViolationCheck(present_scope, ast_tree, "", 's');
        //     // if (typeViolation == -1) {
        //     //     printErrorMessage(ast_tree->line_no);
        //     //     // printf("Type violation error in line %d\n", ast_tree->line_no);
        //     // }
        //     break;
        // }

       
           

        // case 'n':
        //     return ast_tree;
        //     break;
        // case 'N':
        //     return ast_tree;
        //     break;
    

            
    }
    return ast_tree;
}