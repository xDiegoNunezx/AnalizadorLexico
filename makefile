OBJS	= tablas.o tokens.o main.o lex.yy.o
SOURCE	= tablas.c tokens.c main.c lex.yy.c
HEADER	= tablas.h tokens.h lex.yy.h
SOURCEDIR = src
OUT	= analizadorLexico.out
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = -lm -lfl

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

tablas.o: $(SOURCEDIR)/tablas.c
	$(CC) $(FLAGS) $(SOURCEDIR)/tablas.c 

tokens.o: $(SOURCEDIR)/tokens.c
	$(CC) $(FLAGS) $(SOURCEDIR)/tokens.c 

main.o: $(SOURCEDIR)/main.c
	$(CC) $(FLAGS) $(SOURCEDIR)/main.c 

lex.yy.o: $(SOURCEDIR)/lex.yy.c
	$(CC) $(FLAGS) $(SOURCEDIR)/lex.yy.c 
lex.yy.c: analizadorLexico.l
	flex $(SOURCEDIR)/analizadorLexico.l


clean:
	rm -f $(OBJS) $(OUT)