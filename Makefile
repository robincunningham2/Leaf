_OS	?=
CC	?= cc
LEAF	?= ./leaf
CFLAGS	?=
FILES	?= src/Main.c \
		src/Lexer.c \
		src/memory.c \
		src/Parser.c \
		src/Helper.c \
		src/Array.c \
		src/Module.c \
		src/Lexer/lex.yy.c

FLEX	:= $(shell command -v lex 2> /dev/null)
COMP	:= $(shell command -v $(CC) 2> /dev/null)

CFLAGS += -ljson-c

ifeq ($(OS),Windows_NT)
    _OS := Windows
else
    _OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(_OS),Windows)
	CC := gcc.exe
	LEAF := ./leaf.exe
endif

.PHONY: check all

all: check
	cd src/Lexer/ && lex lexer.l

ifeq ($(_OS),Windows)
	$(CC) $(CFLAGS) -std=c99 -o $(LEAF) $(FILES) -Wno-return-type
else
	$(CC) $(CFLAGS) -std=gnu99 -o $(LEAF) $(FILES) -Wno-return-type
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
