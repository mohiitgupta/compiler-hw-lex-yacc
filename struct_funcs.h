#include<stdlib.h>
extern struct symbol_node *symbols[100000];
extern int length; 
extern int line_numbers;
extern int block_level;
extern struct scope_node *present_scope;
//#include <stdbool.h>
//typedef enum { false, true } bool;
struct scope_node
{
  int scope_level;
  struct scope_node * parent;
  struct symbol_node *symbols[10000];
  int len_symbol_table;

};
struct symbol_node
{
  char * name;
  void * value;
  char * type;
  int line;
  char * line_update;
  //int block_level;
  // struct symbol_node * next;
  // struct symbol_node * prev;
  // struct symbol_node * hnext;
  // struct symbol_node * hprev;
};

struct ast_node 
{
  int node_type;
  struct ast_node * left;
  struct ast_node * right;
  int block_level;
};

struct ast_symbol_reference_node // for symbol references
{
  int node_type;
  struct symbol_node * symbol;
  int block_level;
};

struct ast_if_node // for "if/else" statements
{
  int node_type;
  struct ast_node * condition;
  struct ast_node * if_branch;
  struct ast_node * else_branch;
  int block_level;
};

struct ast_while_node // for "while" statements
{
  int node_type;
  struct ast_node * condition;
  struct ast_node * while_branch;
  int block_level;
};

struct ast_assignment_node // for assignment expressions
{
  int node_type;
  struct symbol_node * symbol;
  struct ast_node * value;
  int block_level;
};
struct ast_number_node // for constant floating-point numbers
{
  int node_type;
  int value;
  int block_level;
};
struct ast_string_node // for constant floating-point numbers
{
  int node_type;
  char * value;
  int block_level;
};
struct ast_boolean_node // for constant floating-point numbers
{
  int node_type;
  int value;
  int block_level;
};

struct ast_for_sum_node // for "if/else" statements
{
  int node_type;
  struct symbol_node * symbol;
  int left_value;
  int right_value;
  struct ast_node * expression;
  int block_level;
};

static struct ast_node * mk_ast_for_sum_node (struct symbol_node * symbol, int left_value, int right_value, struct ast_node * expression)
{
  struct ast_for_sum_node * ast_node = (struct ast_for_sum_node *) malloc (sizeof (struct ast_for_sum_node));

  ast_node->node_type = 'F';
  ast_node->symbol = symbol;
  ast_node->left_value = left_value;
  ast_node->right_value = right_value;
  ast_node->expression = expression;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_node (int node_type, struct ast_node * left, struct ast_node * right)
{
  struct ast_node * ast_node = (struct ast_node *) malloc (sizeof (struct ast_node));
  ast_node->node_type = node_type;
  ast_node->left = left;
  ast_node->right = right;
  ast_node->block_level = block_level;
  //printf("block level is %d", block_level);
  return ast_node;
}

static struct ast_node * mk_ast_symbol_reference_node (struct symbol_node * symbol)
{
  struct ast_symbol_reference_node * ast_node = (struct ast_symbol_reference_node *) malloc (sizeof (struct ast_symbol_reference_node));
  ast_node->node_type = 's';
  ast_node->symbol = symbol;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_if_node (struct ast_node * condition, struct ast_node * if_branch, struct ast_node * else_branch)
{
  struct ast_if_node * ast_node = (struct ast_if_node *) malloc (sizeof (struct ast_if_node));

  ast_node->node_type = 'I';
  ast_node->condition = condition;
  ast_node->if_branch = if_branch;
  ast_node->else_branch = else_branch;
  ast_node->block_level = block_level;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_while_node (struct ast_node * condition, struct ast_node * while_branch)
{
  struct ast_while_node * ast_node = (struct ast_while_node *) malloc (sizeof (struct ast_while_node));

  ast_node->node_type = 'W';
  ast_node->condition = condition;
  ast_node->while_branch = while_branch;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_assignment_node (struct symbol_node * symbol, struct ast_node * value)
{
  //fprintf(stderr, "test" );
  //printf("length is %d", length);
  struct ast_assignment_node * ast_node = (struct ast_assignment_node *) malloc (sizeof (struct ast_assignment_node));
  ast_node->node_type = 'A';
  ast_node->symbol = symbol;
  ast_node->value = value;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}
static struct ast_node * mk_ast_number_node (int value)
{
  //fprintf(stderr, "test2" );
  //printf("number is %d", value);
  struct ast_number_node * ast_node = (struct ast_number_node *) malloc (sizeof (struct ast_number_node));
  ast_node->node_type = 'N';
  ast_node->value = value;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_boolean_node (int value)
{
  //fprintf(stderr, "test2" );
  //printf("number is %d", value);
  struct ast_boolean_node * ast_node = (struct ast_boolean_node *) malloc (sizeof (struct ast_boolean_node));
  ast_node->node_type = 'B';
  ast_node->value = value;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}

static struct ast_node * mk_ast_string_node (char * value)
{
  //fprintf(stderr, "test2" );
  //printf("string is %s", value);
  struct ast_string_node * ast_node = (struct ast_string_node *) malloc (sizeof (struct ast_string_node));
  ast_node->node_type = 'n';
  ast_node->value = value;
  ast_node->block_level = block_level;
  return (struct ast_node *) ast_node;
}


