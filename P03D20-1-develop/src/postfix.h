#ifndef POSTFIX_H
#define POSTFIX_H

#include "list.h"

void infix_to_postfix(struct list *infix, struct list **res);
int check_postfix(struct list *expr);
double calc(struct list *postfix, double x);

#endif
