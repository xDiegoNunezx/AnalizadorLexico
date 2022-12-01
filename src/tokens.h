/*
Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
Fecha de creación: 30/10/2022

En este archivo se definen los tokens, las listas ligadas de tokens y los nodos de las listas ligadas.
*/

#ifndef TOKENS_H
#define TOKENS_H
#include "tablas.h"

/*
    Definición de un Token con dos atributos, clase y valor. 
*/
typedef struct Token{
    int clase;
    int valor;
}Token;
/*
Definición de un nodo para una lista ligada doble de tokens.
*/
typedef struct NodoToken{
    Token *info;
    struct NodoToken *prev;
    struct NodoToken *next;
}NodoToken;

/*
    Definición de una lista ligada doble de tokens con referencias a la cabeza y cola
    de la lista.
*/
typedef struct ListaTokens{
    int tamanio;
    NodoToken *head;
    NodoToken *tail;
}ListaTokens;

// Atomos
typedef struct NodoAtomo{
    char info;
    struct NodoAtomo *next;
}NodoAtomo;

typedef struct ListaAtomos{
    int tamanio;
    NodoAtomo *head;
    NodoAtomo *tail;
}ListaAtomos;

ListaTokens *nueva_lista_tokens();
int nuevo_token_pal_res(ListaTokens* lt, char * pal);
int nuevo_token_ident(ListaTokens *lt, TablaIdentificadores *ti, char *ident);
int nuevo_token_real(ListaTokens *lt, TablaReales *tr, char *num);
int nuevo_token_decimal(ListaTokens *lt, char *num);
int nuevo_token_octal(ListaTokens *lt, char *num);
int nuevo_token_cadena(ListaTokens* lt, Tabla *tc,char *cadena);
int nuevo_token_simbolo(ListaTokens *lt, char *simbolo);
int nuevo_token_operadorA(ListaTokens *lt, char *cadena);
int nuevo_token_operadorR(ListaTokens *lt, char *cadena);
int nuevo_token_asignacion(ListaTokens *lt);
void imprimir_lista_tokens(ListaTokens *lt, FILE* archivoSalida);
ListaAtomos *nueva_lista_atomos(ListaTokens *lt);
#endif