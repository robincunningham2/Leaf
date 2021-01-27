all: both
.PHONY: compile install all

both:
	lex src/Lexer/lexer.l
	@mv lex.yy.c src/Lexer/lex.yy.c

	gcc src/Main.c \
		src/Lexer.c \
		src/memory.c \
		src/Parser.c \
		src/Helper.c \
		src/Array.c \
		src/Lexer/lex.yy.c \
		-o ./leaf -Wno-return-type
	
	cp ./leaf /usr/local/bin/leaf

install:
	lex src/Lexer/lexer.l
	@mv lex.yy.c src/Lexer/lex.yy.c

	gcc src/Main.c \
		src/Lexer.c \
		src/memory.c \
		src/Parser.c \
		src/Helper.c \
		src/Array.c \
		src/Lexer/lex.yy.c \
		-o /usr/local/bin/leaf -Wno-return-type

compile:
	lex src/Lexer/lexer.l
	@mv lex.yy.c src/Lexer/lex.yy.c

	gcc src/Main.c \
		src/Lexer.c \
		src/memory.c \
		src/Parser.c \
		src/Helper.c \
		src/Array.c \
		src/Lexer/lex.yy.c \
		-o ./leaf -Wno-return-type
