#directories with source code .c
CODEDIRS = . src
#directories with headers .h
INCDIRS = . ./include/

#compiler
CC = gcc
#optimization level
OPT = -O0
#c standard
STD = -std=c23
#flags for make to keep track of dependencies in the code
DEPFLAGS = -MP -MD
#flags for included libraries
LIBFLAGS = -lm

CFLAGS = -Wall -Wextra $(foreach HDIR, $(INCDIRS), -I$(HDIR)) $(OPT) $(STD) $(DEPFLAGS) $(LIBFLAGS)

#source code list
#loops thru each CDIR that has source code and grabs all .c files in them, with path relative to the project's root
SRC = $(foreach CDIR, $(CODEDIRS), $(wildcard $(CDIR)/*.c))
#dependencies list
DEP = $(patsubst %.c, %.d, $(SRC))
#.i preprocessed files
#pattern substitution maches the variable % part of the strings and substitutes the explicit text in between
PPC = $(patsubst %.c, build/ppc/%.i, $(SRC))
#.s assembly files
ASM = $(patsubst %.c, build/asm/%.s, $(SRC))
#.o object files 
OBJ = $(patsubst %.c, build/obj/%.o, $(SRC))
#library object
LIB = lib/liblac.a
#executable binary
BIN = main

#build everything
#an interesting pattern would be to run other makefiles within this command. todo maybe?
all: $(BIN) $(LIB) $(OBJ) $(ASM) $(PPC)

#output binary only
bin: $(BIN)
	rm -rf build/*

#output library only
lib: $(LIB)
	rm -rf build/*

#output preprocessed source only
ppc: $(PPC)

#output assembly only
asm: $(ASM)

#output unlinked objects only
obj: $(OBJ)

#rule for binary generation. $^ indicates all files in the input. $< indicates highest priority file only.
$(BIN): $(OBJ)
	$(CC) -o $@ $^

$(LIB): $(OBJ)
	mkdir -p lib
	ar rcs $@ $^

#rule for .i generation
build/ppc/%.i: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -E -o $@ $<

#rule for .s generation
build/asm/%.s: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -S -o $@ $<

#rule for .o generation
build/obj/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

#cleaning script
clean:
	rm -rf $(BIN) build/* lib/*
