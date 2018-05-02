#ifndef hash
#define hash

#include<string.h>
#include"struct_funcs.h"
// struct hash{
//     struct symbol *head;
//     int count;
// };

static struct symbol_node * create_symbol(char *name)
{
    struct symbol_node *newSymbol;

    newSymbol = (struct symbol_node *)malloc(sizeof(struct symbol_node));
    //fprintf(stderr, "hash %s", name);
    newSymbol->name = (char *)malloc(sizeof(name));
    newSymbol->type = "undefined";
    strcpy(newSymbol->name, name);
    //newSymbol->initialize = "notInitialized";
    newSymbol->value = NULL;
    //newSymbol->next = NULL;
    //fprintf(stderr, "hash test4");
    return newSymbol;
}
static struct symbol_node * lookup(char * name) {
    //fprintf(stderr, "hash test1");
    for (int i=0; i < length; i++) {
        if (strcmp(symbols[i]->name, name) == 0) {
            return symbols[i];
        }
    }
    //fprintf(stderr, "hash test2");

    symbols[length++] = create_symbol(name);
    //printf("length = %d", length);
    return symbols[length-1];
}
static struct symbol_node * find(char * name) {
    int positions[200];
    int count = 0;
    //fprintf(stderr, "hash test1");
    for (int i=0; i < length; i++) {
        if (strcmp(symbols[i]->name, name) == 0) {
            positions[count++] = i;
            //return symbols[i];
        }
    }
    // for (int i=0; i < count; i++) {

    // }
    
    return NULL;
}
#endif