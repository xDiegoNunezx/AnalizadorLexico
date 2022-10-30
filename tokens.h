#ifndef TOKENS_H
#define TOKENS_H

typedef struct Token{
    int clase;
    int valor;
}Token;

typedef struct NodoToken{
    Token *info;
    NodoToken *prev;
    NodoToken *next;
}NodoToken;

typedef struct ListaTokens{
    int tamanio;
    NodoToken *head;
    NodoToken *tail;
}ListaTokens;

#endif