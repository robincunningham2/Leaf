all: compile
.PHONY: compile install

install:
	lex src/Lexer/lexer.l
	@mv lex.yy.c src/Lexer/lex.yy.c
	
	gcc src/Lexer.c \
		src/memory.c \
		src/Parser.c \
		src/Helper.c \
		src/Lexer/lex.yy.c \
		-o /usr/local/bin/leaf

compile:
	lex src/Lexer/lexer.l
	@mv lex.yy.c src/Lexer/lex.yy.c
	
	gcc src/Lexer.c \
		src/memory.c \
		src/Parser.c \
		src/Helper.c \
		src/Lexer/lex.yy.c \
		-o ./leaf
