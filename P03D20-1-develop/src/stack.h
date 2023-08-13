#ifndef STACK_H
#define STACK_H

#include "lexer.h"
#include "list.h"

typedef struct list *stack;

void push_stack(stack *s, const struct token *data);
void pop_stack(stack *s, struct token *res);
int is_empty_stack(const stack s);

#endif
