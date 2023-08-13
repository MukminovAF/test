#include "stack.h"

#include <stdlib.h>

void push_stack(stack *s, const struct token *data) {
    stack tmp = malloc(sizeof(*tmp));
    tmp->data = *data;
    tmp->next = *s;
    *s = tmp;
}

void pop_stack(stack *s, struct token *res) {
    if (*s != NULL) {
        *res = (*s)->data;
        stack tmp = *s;
        *s = (*s)->next;
        free(tmp);
    }
}

int is_empty_stack(const stack s) { return s == NULL; }
