
all: compile

compile:
	lex Scanner/scanner.l
	@mv lex.yy.c Scanner/lex.yy.c
	cc Scanner/scanner.c Scanner/lex.yy.c Parser/memory.c -o ./a

	@echo "\nA is installed!"
