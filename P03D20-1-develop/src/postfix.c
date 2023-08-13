#include "postfix.h"

#include <stdlib.h>

#include "list.h"
#include "stack.h"

void handle_paren(stack *buf, struct list **res) {
    struct token t;
    for (pop_stack(buf, &t); t.kind != LEFT_PAREN; pop_stack(buf, &t)) {
        append_list(res, &t);
        *res = (*res)->next;
    }
    if (is_empty_stack(*buf)) *res = NULL;
}

void handle_operator(stack *buf, struct list **res, struct token *op) {
    struct token t;
    for (pop_stack(buf, &t); t.kind != LEFT_PAREN && t.precedence < op->precedence; pop_stack(buf, &t)) {
        append_list(res, &t);
        *res = (*res)->next;
    }
    push_stack(buf, &t);
    push_stack(buf, op);
}

void flush_buffer(stack *buf, struct list **res) {
    struct token t;
    for (pop_stack(buf, &t); t.kind != LEFT_PAREN; pop_stack(buf, &t)) {
        append_list(res, &t);
        *res = (*res)->next;
    }
    if (!is_empty_stack(*buf)) {
        delete_list(*buf);
        *res = NULL;
    }
}

void infix_to_postfix(struct list *infix, struct list **res) {
    stack buf = NULL;
    struct token t = {.kind = LEFT_PAREN};
    push_stack(&buf, &t);
    append_list(res, &t);
    struct list *p = *res;
    for (; infix != NULL && p != NULL; infix = infix->next) {
        t = infix->data;
        if (t.kind == CONSTANT || t.kind == VARIABLE) {
            append_list(&p, &t);
            p = p->next;
        } else if (t.kind == LEFT_PAREN) {
            push_stack(&buf, &t);
        } else if (t.kind == RIGHT_PAREN) {
            handle_paren(&buf, &p);
        } else {
            handle_operator(&buf, &p, &t);
        }
    }
    if (p != NULL) {
        flush_buffer(&buf, &p);
    }
    if (p == NULL) {
        delete_list(*res);
        *res = NULL;
    } else {
        p = *res;
        *res = (*res)->next;
        free(p);
        free(buf);
    }
}

int check_postfix(struct list *expr) {
    int cnt = 0, f = 1;
    for (; expr != NULL && f; expr = expr->next) {
        cnt += 1 - expr->data.valence;
        if (cnt <= 0) f = 0;
    }
    return cnt == 1;
}

double calc(struct list *postfix, double x) {
    stack buf = NULL;
    struct token t, lhs, rhs;
    for (; postfix != NULL; postfix = postfix->next) {
        t = postfix->data;
        if (t.kind == VARIABLE) {
            t.data.val = x;
            push_stack(&buf, &t);
        } else if (t.kind == CONSTANT) {
            push_stack(&buf, &t);
        } else if (t.kind == UNARY_OP) {
            pop_stack(&buf, &rhs);
            rhs.data.val = t.data.unary(rhs.data.val);
            push_stack(&buf, &rhs);
        } else {
            pop_stack(&buf, &rhs);
            pop_stack(&buf, &lhs);
            rhs.data.val = t.data.binary(lhs.data.val, rhs.data.val);
            push_stack(&buf, &rhs);
        }
    }
    pop_stack(&buf, &t);
    return t.data.val;
}
