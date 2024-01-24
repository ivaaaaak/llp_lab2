all: build

build:
	bison -d -Wall -o src/bison+flex/y.tab.c src/bison+flex/parser.y
	flex -o src/bison+flex/lex.yy.c src/bison+flex/lexer.l
	gcc -g src/main.c src/printer.c src/query.c src/bison+flex/lex.yy.c src/bison+flex/y.tab.c -o main

%PHONY: clean

clean:
	rm -f src/bison+flex/lex.yy.c main src/bison+flex/y.tab.c src/bison+flex/y.tab.h

run:
	./main