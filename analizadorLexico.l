%{
#include <stdio.h>
#include <stdlib.h>
#include "tablas.h"
/* Programa que lee un programa y hace elreconocimiento de identificadores, 
palabras reservadas y enteros de un lenguaje x
*/
FILE *archSal;
TablaReales *tablaR;
TablaCadenas *tablaC;
TablaIdentificadores *tablaI;
void realEncontrado(char *cadena, int tam);
void cadenaEncontrada(char *cadena, int tam);
void identificadorEncontrado(char *cadena);
%}
espacio         [ ]
salto           [\n]
palres          alternative|big|evaluate|instead|large|loop|make|number|other|real|repeat|select|small|step|stop|symbol|throw
letMayus        [A-Z]
letMinus        [a-z]
dig             [0-9]
ident           \$({letMayus}|{letMinus})+
real            [0-9]*\.[0-9]+
decimal         ([1-9][0-9]*)|0
octal           [Oo][0-7]+
cadena          (\"[^"'\n][^"'\n]+\")|('[^'\n]')|(\"'\")
simEsp          [{}()\[\],;:]
operArit        [+\-*/%\^]
opRel           <=|>=|==|<|>|!=
opAsig          =

%%
{espacio}
{salto}
{palres}        fprintf(archSal,"%s es unapalabra reservada\n", yytext);
{ident}         identificadorEncontrado(yytext);
{real}          realEncontrado(yytext, yyleng);
{decimal}       fprintf(archSal,"decimal %s\n",yytext);
{octal}         fprintf(archSal,"octal %s\n",yytext);
{cadena}        cadenaEncontrada(yytext, yyleng);
{simEsp}        fprintf(archSal,"%s es un simbolo especial\n", yytext);
{operArit}      fprintf(archSal,"%s es un operador aritmetico\n", yytext);
{opRel}         fprintf(archSal,"%s es un operador relacional\n", yytext);
{opAsig}        fprintf(archSal,"%s es un operador de asignacion\n", yytext);
.               fprintf(archSal,"%s es un error, no se reconoce\n", yytext);
%%



int analizadorLexico(char* archivoEntrada, TablaReales *tr, TablaCadenas *tc, TablaIdentificadores *ti){
        yyin = fopen(archivoEntrada,"r");
        archSal = fopen("lex_an_output.txt","w");
        tablaR = tr;
        tablaC = tc;
        tablaI = ti;
        yylex();
        fclose(archSal);
}

void realEncontrado(char *cadena, int tam){
        fprintf(archSal,"%s es un real\n", yytext);
        insertar_tabla(tablaR, yytext);
}

void cadenaEncontrada(char *cadena, int tam){
        fprintf(archSal,"%s es una cadena con tamanio %d \n", yytext, yyleng);
        insertar_tabla(tablaC, yytext);
}

void identificadorEncontrado(char *cadena){
        fprintf(archSal,"%s es un identificador\n", cadena);
        insertar_tabla_identificadores(tablaI, cadena);
}

