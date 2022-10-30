#! /bin/bash
flex analizadorLexico.l
gcc lex.yy.c tablas.c main.c -lfl
./a.out prueba.u
