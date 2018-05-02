#include<stdlib.h>
extern struct symbol_node *symbols[100000];
extern int length; 
extern int line_numbers;
extern int line_no;
extern struct scope_node *present_scope;
extern int yylineno;
//#include <stdbool.h>
//typedef enum { false, true } bool;
struct scope_node
{
  int scope_level;
  struct scope_node * parent;
  struct symbol_node *symbols[10000];
  int len_symbol_table;
  int len_child_scopes;
  struct scope_node *child_scopes[100];
  int current_child_scope;

};
struct symbol_node
{
  char * name;
  void * value;
  char * type;
  char * declare;
  int line;
  char * line_update;
  //int line_no;
  // struct symbol_node * next;
  // struct symbol_node * prev;
  // struct symbol_node * hnext;
  // struct symbol_node * hprev;
};

struct ast_node 
{
  int node_type;
  int line_no;
  int def_length;
  int use_length;
  int live_in_length;
  int live_out_length;
  int line_no_2;
  int len_non_declared_symbols;


  char * def[100];
  
  char * use[100];
  
  char * live_in[100];
  
  char * live_out[100];
  

  struct ast_node * condition;
  struct ast_node * left;
  struct ast_node * right;
  struct symbol_node * symbol;
  struct ast_node * parent_node;
  struct symbol_node * non_declared_symbols[10000];
  

};

// struct ast_symbol_reference_node // for symbol references
// {
//   int node_type;
//   int line_no;
//   struct symbol_node * symbol;
// };

// struct ast_if_node // for "if/else" statements
// {
//   int node_type;
//   struct ast_node * condition;
//   struct ast_node * if_branch;
//   struct ast_node * right;
//   int line_no;
// };

// struct ast_while_node // for "while" statements
// {
//   int node_type;
//   int line_no;
//   int def_length;
//   int use_length;
//   int live_in_length;
//   int live_out_length;
//   int line_no_2;


//   char * def[100];
  
//   char * use[100];
  
//   char * live_in[100];
  
//   char * live_out[100];
//   struct ast_node * condition;
//   struct ast_node * while_branch;
// };

struct ast_assignment_node // for assignment expressions
{
  int node_type;
  int line_no;
  int def_length;
  int use_length;
  int live_in_length;
  int live_out_length;
  char * def[100];
  
  char * use[100];
  
  char * live_in[100];
  
  char * live_out[100];
  

  struct ast_node * symbol;
  struct ast_node * value;
  struct ast_node * parent_node;
};
struct ast_number_node // for constant floating-point numbers
{
  int node_type;
  int line_no;
  int value;
  int def_length;
  int use_length;
  int live_in_length;
  int live_out_length;
  int line_no_2;


  char * def[100];
  
  char * use[100];
  
  char * live_in[100];
  
  char * live_out[100];
};
struct ast_string_node // for constant floating-point numbers
{
  int node_type;
  int line_no;
  int def_length;
  int use_length;
  int live_in_length;
  int live_out_length;
  int line_no_2;


  char * def[100];
  
  char * use[100];
  
  char * live_in[100];
  
  char * live_out[100];
  char * value;
};
struct ast_boolean_node // for constant floating-point numbers
{
  int node_type;
   int line_no;
  int value;
  int def_length;
  int use_length;
  int live_in_length;
  int live_out_length;
  int line_no_2;


  char * def[100];
  
  char * use[100];
  
  char * live_in[100];
  
  char * live_out[100];
};

struct ast_for_sum_node // for "if/else" statements
{
  int node_type;
  int line_no;
  int line_no_2;

  int value;
  int def_length;
  int use_length;
  int live_in_length;
  int live_out_length;


  char * def[100];
  
  char * use[100];
  
  char * live_in[100];
  
  char * live_out[100];


  struct ast_node * symbol;
  int left_value;
  int right_value;
  struct ast_node * expression;
};

static struct ast_node * mk_ast_for_sum_node (struct ast_node * symbol, int left_value, int right_value, struct ast_node * expression)
{
  struct ast_for_sum_node * ast_node = (struct ast_for_sum_node *) malloc (sizeof (struct ast_for_sum_node));

  ast_node->node_type = 'F';
  ast_node->symbol = symbol;
  ast_node->left_value = left_value;
  ast_node->right_value = right_value;
  ast_node->expression = expression;
  ast_node->line_no = yylineno;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_node (int node_type, struct ast_node * left, struct ast_node * right)
{
  // printf("line no for this node is %d", yylineno);
  struct ast_node * ast_node = (struct ast_node *) malloc (sizeof (struct ast_node));
  ast_node->node_type = node_type;
  ast_node->left = left;
  ast_node->right = right;
  ast_node->line_no = yylineno;
  ast_node->def_length = 0;
  ast_node->use_length = 0;
  ast_node->parent_node = NULL;
  ast_node->len_non_declared_symbols = 0;

  //printf("block level is %d", line_no);
  return ast_node;
}

static struct ast_node * mk_ast_symbol_reference_node (struct symbol_node * symbol)
{
  // struct ast_symbol_reference_node * ast_node = (struct ast_symbol_reference_node *) malloc (sizeof (struct ast_symbol_reference_node));
  struct ast_node * ast_node = (struct ast_node *) malloc (sizeof (struct ast_node));

  ast_node->node_type = 's';
  ast_node->symbol = symbol;
  ast_node->line_no = yylineno;
  // printf("line number is %d\n", ast_node->line_no);
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_if_node (struct ast_node * condition, struct ast_node * if_branch, struct ast_node * else_branch)
{
  // struct ast_if_node * ast_node = (struct ast_if_node *) malloc (sizeof (struct ast_if_node));
  struct ast_node * ast_node = (struct ast_node *) malloc (sizeof (struct ast_node));
  ast_node->node_type = 'I';
  ast_node->condition = condition;
  ast_node->left = if_branch;
  ast_node->right = else_branch;
  // printf("else pointer for if %p\n", NULL);
  // ast_node->line_no = line_no;
  ast_node->line_no = yylineno;

  if (if_branch->node_type == 'A') {
    struct ast_assignment_node * left_node = (struct ast_assignment_node *)if_branch;
    left_node->parent_node = ast_node;
  } else {
    if_branch->parent_node = ast_node;
  }
  if (else_branch != NULL) {
    if (else_branch->node_type == 'A') {
      struct ast_assignment_node * left_node = (struct ast_assignment_node *)else_branch;
      left_node->parent_node = ast_node;
    } else {
      else_branch->parent_node = ast_node;
    }
  }
  return ast_node;
}

static struct ast_node * mk_ast_while_node (struct ast_node * condition, struct ast_node * while_branch)
{
  // struct ast_while_node * ast_node = (struct ast_while_node *) malloc (sizeof (struct ast_while_node));
  struct ast_node * ast_node = (struct ast_node *) malloc (sizeof (struct ast_node));

  ast_node->node_type = 'W';
  ast_node->condition = condition;
  // ast_node->while_branch = while_branch;
  ast_node->left = while_branch;
  ast_node->right = NULL;
  ast_node->line_no = yylineno;

  if (while_branch->node_type == 'A') {
    struct ast_assignment_node * left_node = (struct ast_assignment_node *)while_branch;
    left_node->parent_node = ast_node;
  } else {
    while_branch->parent_node = ast_node;
  }
  return ast_node;
}

static struct ast_node * mk_ast_assignment_node (struct ast_node * symbol, struct ast_node * value)
{
  //fprintf(stderr, "test" );
  // printf("symbol line is %d", symbol->line_no);
  struct ast_assignment_node * ast_node = (struct ast_assignment_node *) malloc (sizeof (struct ast_assignment_node));
  ast_node->node_type = 'A';
  ast_node->symbol = symbol;
  ast_node->value = value;
  ast_node->line_no = yylineno;
  ast_node->parent_node = NULL;
  return (struct ast_node *) ast_node;
}
static struct ast_node * mk_ast_number_node (int value)
{
  //fprintf(stderr, "test2" );
  //printf("number is %d", value);
  struct ast_number_node * ast_node = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
  ast_node->node_type = 'N';
  ast_node->value = value;
  ast_node->line_no = yylineno;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_boolean_node (int value)
{
  //fprintf(stderr, "test2" );
  //printf("number is %d", value);
  struct ast_boolean_node * ast_node = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
  ast_node->node_type = 'B';
  ast_node->value = value;
  ast_node->line_no = yylineno;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_string_node (char * value)
{
  //fprintf(stderr, "test2" );
  //printf("string is %s", value);
  struct ast_string_node * ast_node = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
  ast_node->node_type = 'n';
  ast_node->value = value;
  ast_node->line_no = yylineno;
  return (struct ast_node *) ast_node;
}


