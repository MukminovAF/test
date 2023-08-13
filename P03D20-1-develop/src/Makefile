CC = gcc
CFLAGS = -Wall -Wextra -Werror
BUILD = ../build/

all: $(BUILD)graph

rebuild: clean all

$(BUILD)graph: graph.c $(BUILD)lexer.o $(BUILD)postfix.o $(BUILD)printer.o $(BUILD)stack.o $(BUILD)list.o
	$(CC) $(CFLAGS) graph.c $(BUILD)lexer.o $(BUILD)postfix.o $(BUILD)printer.o $(BUILD)stack.o $(BUILD)list.o -o $(BUILD)graph

$(BUILD)lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c -o $(BUILD)lexer.o

$(BUILD)postfix.o: postfix.c postfix.h
	$(CC) $(CFLAGS) -c postfix.c -o $(BUILD)postfix.o

$(BUILD)printer.o: printer.c printer.h
	$(CC) $(CFLAGS) -c printer.c -o $(BUILD)printer.o

$(BUILD)stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c -o $(BUILD)stack.o

$(BUILD)list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c -o $(BUILD)list.o

clean:
	rm -f $(BUILD)*.o $(BUILD)graph
