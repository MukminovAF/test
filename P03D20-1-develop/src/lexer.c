#include "lexer.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

void set_token(struct token *t, int kind, void *data, int precedence, int valence) {
    t->kind = kind;
    if (kind == UNARY_OP) {
        t->data.unary = (double (*)(double))data;
    } else if (kind == BINARY_OP) {
        t->data.binary = (double (*)(double, double))data;
    } else if (kind == CONSTANT) {
        t->data.val = *((double *)data);
    } else {
        t->data.val = 0;
    }
    t->precedence = precedence;
    t->valence = valence;
}

double add(double a, double b) { return a + b; }

double sub(double a, double b) { return a - b; }

double mul(double a, double b) { return a * b; }

double divide(double a, double b) { return a / b; }

double neg(double a) { return -a; }

double cot(double a) { return 1 / tan(a); }

int is_digit(int ch) { return '0' <= ch && ch <= '9'; }

int is_alpha(int ch) { return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z'); }

void get_num(struct token *t, int ch) {
    double num = ch - '0';
    ch = getchar();
    while (is_digit(ch)) {
        num *= 10;
        num += ch - '0';
        ch = getchar();
    }
    if (ch == '.') {
        double frac = 0.1;
        ch = getchar();
        while (is_digit(ch)) {
            num += (ch - '0') * frac;
            frac /= 10;
            ch = getchar();
        }
    }
    ungetc(ch, stdin);
    set_token(t, CONSTANT, &num, NONE, 0);
}

void get_word(struct token *t, int ch) {
    char word[5] = {ch};
    if (!strcmp(word, "x")) {
        set_token(t, VARIABLE, NULL, NONE, 0);
    } else if ((word[1] = getchar()) != EOF && !strcmp(word, "ln")) {
        set_token(t, UNARY_OP, log, UNARY, 1);
    } else if ((word[2] = getchar()) != EOF && !strcmp(word, "sin")) {
        set_token(t, UNARY_OP, sin, UNARY, 1);
    } else if (!strcmp(word, "cos")) {
        set_token(t, UNARY_OP, cos, UNARY, 1);
    } else if (!strcmp(word, "tan")) {
        set_token(t, UNARY_OP, tan, UNARY, 1);
    } else if (!strcmp(word, "ctg")) {
        set_token(t, UNARY_OP, cot, UNARY, 1);
    } else if ((word[3] = getchar()) != EOF && !strcmp(word, "sqrt")) {
        set_token(t, UNARY_OP, sqrt, UNARY, 1);
    } else {
        set_token(t, UNKNOWN, NULL, NONE, NONE);
    }
}

int is_operator(int ch) { return ch == '~' || ch == '+' || ch == '-' || ch == '*' || ch == '/'; }

void set_operator(struct token *t, int ch) {
    if (ch == '~') {
        set_token(t, UNARY_OP, neg, UNARY, 1);
    } else if (ch == '+') {
        set_token(t, BINARY_OP, add, ADDITIVE, 2);
    } else if (ch == '-') {
        set_token(t, BINARY_OP, sub, ADDITIVE, 2);
    } else if (ch == '*') {
        set_token(t, BINARY_OP, mul, MULTIPLICATIVE, 2);
    } else if (ch == '/') {
        set_token(t, BINARY_OP, divide, MULTIPLICATIVE, 2);
    }
}

void get_token(struct token *t) {
    int ch = getchar();
    if (is_digit(ch)) {
        get_num(t, ch);
    } else if (is_alpha(ch)) {
        get_word(t, ch);
    } else if (is_operator(ch)) {
        set_operator(t, ch);
    } else if (ch == '(') {
        set_token(t, LEFT_PAREN, NULL, NONE, NONE);
    } else if (ch == ')') {
        set_token(t, RIGHT_PAREN, NULL, NONE, NONE);
    } else if (ch == '\n' || ch == EOF) {
        set_token(t, EMPTY, NULL, NONE, NONE);
    } else {
        set_token(t, UNKNOWN, NULL, NONE, NONE);
    }
}

void get_expression(struct list **res) {
    struct token t;
    set_token(&t, LEFT_PAREN, NULL, NONE, NONE);
    append_list(res, &t);
    struct list *p = *res;
    for (get_token(&t); t.kind != EMPTY && t.kind != UNKNOWN; get_token(&t)) {
        append_list(&p, &t);
        p = p->next;
    }
    if (t.kind == EMPTY) {
        set_token(&t, RIGHT_PAREN, NULL, NONE, NONE);
        append_list(&p, &t);
    } else {
        delete_list(*res);
        *res = NULL;
    }
}
