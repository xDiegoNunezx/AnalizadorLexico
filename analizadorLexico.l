%{
#include <stdio.h>
#include <stdlib.h>
#include "tablas.h"
#include "tokens.h"
/* Programa que lee un programa y hace elreconocimiento de identificadores, 
palabras reservadas y enteros de un lenguaje x
*/
FILE *archSal;
TablaReales *tablaR;
TablaCadenas *tablaC;
TablaIdentificadores *tablaI;
ListaTokens *listaT;

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
noIdent         {dig}*({letMayus}|{letMinus})({letMayus}|{letMinus}|{dig})*
real            {dig}*\.{dig}+
noDecimal       0[0-9]+
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
{noDecimal}     fprintf(archSal,"%s es un error, no se reconoce\n", yytext);
{palres}        nuevo_token_pal_res(listaT, yytext);       
 
{ident}         nuevo_token_ident(listaT, tablaI, yytext);
{real}          nuevo_token_real(listaT, tablaR, yytext);
{decimal}       nuevo_token_decimal(listaT, yytext);
{octal}         nuevo_token_octal(listaT, yytext);
{cadena}        nuevo_token_cadena(listaT, tablaC, yytext);
{simEsp}        nuevo_token_simbolo(listaT, yytext);
{operArit}      nuevo_token_operadorA(listaT, yytext);
{opRel}         nuevo_token_operadorR(listaT, yytext);
{opAsig}        nuevo_token_asignacion(listaT);
{noIdent}       fprintf(archSal,"%s es un error, no se reconoce\n", yytext);
.               fprintf(archSal,"%s es un error, no se reconoce\n", yytext);
%%



int analizadorLexico(FILE* archivoEntrada, TablaReales *tr, TablaCadenas *tc, TablaIdentificadores *ti, ListaTokens *lt){
        yyin = archivoEntrada;
        archSal = fopen("lex_an_error.log","w");
        tablaR = tr;
        tablaC = tc;
        tablaI = ti;
        listaT = lt;
        yylex();
        fclose(archSal);
}
