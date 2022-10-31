#ifndef TOKENS_H
#define TOKENS_H
#include "tablas.h"
typedef struct Token{
    int clase;
    int valor;
}Token;

typedef struct NodoToken{
    Token *info;
    struct NodoToken *prev;
    struct NodoToken *next;
}NodoToken;

typedef struct ListaTokens{
    int tamanio;
    NodoToken *head;
    NodoToken *tail;
}ListaTokens;

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
void imprimir_lista_tokens(ListaTokens *lt);
#endif