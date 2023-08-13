#ifndef LIST_H
#define LIST_H

#include "lexer.h"

struct list {
    struct token data;
    struct list *next;
};

void append_list(struct list **list, const struct token *data);
void delete_list(struct list *list);

#endif
