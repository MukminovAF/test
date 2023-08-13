#ifndef LEXER_H
#define LEXER_H

#define UNKNOWN -1
#define EMPTY 0
#define VARIABLE 1
#define CONSTANT 2
#define UNARY_OP 3
#define BINARY_OP 4
#define LEFT_PAREN 5
#define RIGHT_PAREN 6

#define NONE -1
#define UNARY 1
#define ADDITIVE 2
#define MULTIPLICATIVE 3

struct token {
    int kind;
    union {
        double val;
        double (*unary)(double);
        double (*binary)(double, double);
    } data;
    int precedence, valence;
};

struct list;
void get_expression(struct list **res);

double sub(double, double);
#endif
