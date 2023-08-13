#include "list.h"

#include <stdlib.h>

void append_list(struct list **list, const struct token *data) {
    struct list *p = malloc(sizeof(*p));
    p->data = *data;
    p->next = NULL;
    if (*list == NULL) {
        *list = p;
    } else {
        (*list)->next = p;
    }
}

void delete_list(struct list *list) {
    if (list != NULL) {
        delete_list(list->next);
        free(list);
    }
}
