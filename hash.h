
struct symbol_node
{
  char * name;
  int value;
  //struct symbol_node *next;
};

// struct hash{
//     struct symbol *head;
//     int count;
// };
struct symbol_node *symbols[100000];
int length = 0;
struct symbol_node * create_symbol(char *name)
{
    struct symbol_node *newSymbol;

    newSymbol = (struct symbol_node *)malloc(sizeof(struct symbol_node));
    strcpy(newSymbol->name, name);
    // newSymbol->value = NULL;
    //newSymbol->next = NULL;
    return newSymbol;
}
struct symbol_node * lookup(char * name) {
    for (int i=0; i < length; i++) {
        if (strcmp(symbols[i]->name, name) == 0) {
            return symbols[i];
        }
    }
    symbols[length++] = create_symbol(name);
    return symbols[length-1];
}