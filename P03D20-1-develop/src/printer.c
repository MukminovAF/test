#include "printer.h"

#include <math.h>
#include <stdio.h>

#include "list.h"
#include "postfix.h"

void make_graph(int graph[ROWS][COLS], struct list *expr) {
    for (int i = 0; i < COLS; i++) {
        double x = 4 * M_PI * i / (COLS - 1);
        double y = calc(expr, x);
        int j = round((y + 1) * (ROWS - 1) / 2);
        if (j >= 0 && j < ROWS) {
            graph[j][i] = 1;
        }
    }
}

void print_graph(int graph[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", graph[i][j] ? '*' : '.');
        }
        printf("\n");
    }
}
