_OS	?=
CC	?= cc
LEAF	?= ./leaf
CFLAGS	?=
IGNORE	?=
FILES	?= src/Main.c \
			src/Helper.c \
			src/Memory.c \
			src/Lexer.c \
			src/Parser.c \
			src/Lexer/lex.yy.c

CFLAGS += -ljson-c
IGNORE += -Wno-return-stack-address

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
	cd ./src/Lexer/ && lex lexer.l

ifeq ($(_OS),Windows)
	$(CC) $(CFLAGS) -std=c99 -o $(LEAF) $(FILES) $(IGNORE)
else
	$(CC) $(CFLAGS) -std=gnu99 -o $(LEAF) $(FILES) $(IGNORE)
endif

	@# @echo "\nLeaf `$(LEAF) -v` has been built successfully"
	@echo "\nLeaf has been built successfully"

check:
ifeq ($(_OS),Unknown)
	echo "Unknown system OS"
	exit 1
endif
