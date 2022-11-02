MKDIR   := mkdir
RMDIR   := rm -rf 
CC      := gcc
BIN     := ./bin
OBJ     := ./obj
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
EXE     := $(BIN)/main.out


OS := $(uname)
ifeq ($(OS), Darwin)
LDFLAGS := -lfl -lm
else
LDFLAGS := -ll -lm
endif

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) | $(BIN)
	$(CC)  $^ -o $@ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

$(SRC)/lex.yy.c: $(SRC)/analizadorLexico.l 
	flex -o $(SRC)/lex.yy.c $(SRC)/analizadorLexico.l

run: $(EXE)
	$<

clean:
	$(RMDIR) $(OBJ) $(BIN)