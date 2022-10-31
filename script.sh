#! /bin/bash
clear
flex analizadorLexico.l
gcc *.c -g -lfl -lm
./a.out prueba.u
