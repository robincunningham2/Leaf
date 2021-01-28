_OS		?=
CC		?= cc
MV		?= mv
LEAF	?= ./leaf
FILES	?= src/Main.c \
			src/Lexer.c \
			src/memory.c \
			src/Parser.c \
			src/Helper.c \
			src/Array.c \
			src/Lexer/lex.yy.c

FLEX	:= $(shell command -v lex 2> /dev/null)
COMP	:= $(shell command -v $(CC) 2> /dev/null)

ifeq ($(OS),Windows_NT)
    _OS := Windows
else
    _OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(_OS),Windows)
	CC := gcc.exe
	LEAF := ./leaf.exe
	MV := move
endif

.PHONY: check all

all: check
	lex src/Lexer/lexer.l
	$(MV) lex.yy.c src/Lexer/lex.yy.c

ifeq ($(_OS),Windows)
	$(CC) -std=c99 -o $(LEAF) $(FILES) -Wno-return-type
else
	$(CC) -std=gnu99 -o $(LEAF) $(FILES) -Wno-return-type
endif

	@echo "\nLeaf `$(LEAF) -v` has been built successfully"

check:
ifeq ($(_OS),Unknown)
	echo "Unknown system OS" && exit 1
endif

ifndef FLEX
	echo "Flex is not installed" && exit 1
endif

ifndef COMP
	echo "GCC is not installed" && exit 1
endif
