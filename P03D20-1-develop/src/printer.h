#ifndef PRINTER_H
#define PRINTER_H

#include "list.h"

#define ROWS 25
#define COLS 80

void make_graph(int graph[ROWS][COLS], struct list *expr);
void print_graph(int graph[ROWS][COLS]);

#endif
