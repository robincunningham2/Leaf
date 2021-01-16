all: compile
.PHONY: compile install

install:
	lex Scanner/scanner.l
	@mv lex.yy.c Scanner/lex.yy.c
	
	cc Scanner/scanner.c \
		Scanner/lex.yy.c \
		Parser/memory.c \
		Parser/parser.c \
		-o /usr/local/bin/leaf

compile:
	lex Scanner/scanner.l
	@mv lex.yy.c Scanner/lex.yy.c
	
	cc Scanner/scanner.c \
		Scanner/lex.yy.c \
		Parser/memory.c \
		Parser/parser.c \
		-o ./leaf
