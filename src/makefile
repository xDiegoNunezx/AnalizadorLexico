OBJS	= tablas.o tokens.o main.o lex.yy.o
SOURCE	= tablas.c tokens.c main.c lex.yy.c
HEADER	= tablas.h tokens.h lex.yy.h
OUT	= analizadorLexico.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm -lfl

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

tablas.o: tablas.c
	$(CC) $(FLAGS) tablas.c 

tokens.o: tokens.c
	$(CC) $(FLAGS) tokens.c 

main.o: main.c
	$(CC) $(FLAGS) main.c 

lex.yy.o: lex.yy.c
	$(CC) $(FLAGS) lex.yy.c 
lex.yy.c: analizadorLexico.l
	flex analizadorLexico.l


clean:
	rm -f $(OBJS) $(OUT)