#include <stdio.h>

#include "lexer.h"
#include "list.h"
#include "postfix.h"
#include "printer.h"

int main() {
    struct list *infix = NULL, *postfix = NULL;
    get_expression(&infix);
    infix_to_postfix(infix, &postfix);
    if (check_postfix(postfix)) {
        int graph[ROWS][COLS] = {0};
        make_graph(graph, postfix);
        print_graph(graph);
    } else {
        printf("n/a");
    }
    delete_list(infix);
    delete_list(postfix);
    return 0;
}
