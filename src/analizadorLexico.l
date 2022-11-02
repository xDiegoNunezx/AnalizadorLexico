%{


/*
En este archivo se define la función que inicia el analisis léxico y se defienen
las expresiones regulares necesarias para reconocer cada clase de componente léxica 
solicitada.
*/
#include <stdio.h>
#include <stdlib.h>
#include "tablas.h"
#include "tokens.h"


static FILE *archSal;
static TablaReales *tablaR;
static TablaCadenas *tablaC;
static TablaIdentificadores *tablaI;
static ListaTokens *listaT;

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

/*
Función que inicia el analisis léxico. Esta función configura los apuntadores a las tablas de números reales,
cadenas e identificadores así como a la lista de tokens. 
archivoEntrada: Apuntador de tipo FILE que describe el archivo de donde se deben leer las componentes léxicas
tr: Apuntador a un objeto de tipo tabla donde se almancenan los tokens de tipo contante real encontrados.
tc: Apuntador a un objecto de tipo tabla donde se almancenan los tokens de tipo contante cadena.
ti: Apuntador a un objecto de tipo TablaIdentificadores donde se lleva un recuento de los identificadores reconocidos
hasta el momento.
lt: Apuntador a la lista de tokens generados.
*/
void analizadorLexico(FILE* archivoEntrada, TablaReales *tr, TablaCadenas *tc, TablaIdentificadores *ti, ListaTokens *lt){
        yyin = archivoEntrada;
        archSal = fopen("lex_an_error.txt","w");
        tablaR = tr;
        tablaC = tc;
        tablaI = ti;
        listaT = lt;
        yylex();
        fclose(archSal);
}
