#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#include <tablas.h>

Token *nuevo_Token(int clase, int valor){
    Token *nuevoToken = (Token*)malloc(sizeof(Token));
    if(nuevoToken == NULL){
        return NULL;
    }
    nuevoToken->clase = clase;
    nuevoToken->valor = valor;
    return nuevoToken;
}

NodoToken *nuevo_nodo_Token(Token *valor){
    NodoToken *nuevoNodo = (NodoToken*)malloc(sizeof(NodoToken));
    if(nuevoNodo == NULL){
        return NULL;
    }
    nuevoNodo->info = valor;
    nuevoNodo->next = NULL;
    nuevoNodo->prev = NULL;
    return nuevoNodo;

}

ListaTokens *nueva_lista_tokens(){
    ListaTokens *nuevaLista = (ListaTokens*)malloc(sizeof(ListaTokens));
    if(nuevaLista == NULL){
        return NULL;
    }
    
    nuevaLista->head = NULL;
    nuevaLista->tail = NULL;
    nuevaLista->tamanio = 0;
    return nuevaLista;
}

int agregar_lista_tokens(ListaTokens *lt, Token *nuevoToken){
    if(lt == NULL){
        return -1;
    }
    if(nuevoToken == NULL){
        return -1;
    }
    NodoToken *nuevoNodo = nuevo_nodo_Token(nuevoToken);

    if(lt->head == NULL){
        lt->head = nuevoNodo;
    }

    lt->tail->next = nuevoNodo;
    nuevoNodo->prev = lt->tail;
    lt->tail = nuevoNodo;
}



int nuevo_token_pal_res(ListaTokens* lt, char * pal){
    if(lt == NULL){
        return -1;
    }
    const char *palabrasReservadas[17] = {"alternative", "big", "evaluate",
        "instead", "large", "loop", "make", "number", "other", "real",
        "repeat", "select", "small", "step", "stop", "symbol", "throw"};

    int res = busquedaBinaria(palabrasReservadas, 0, 16, pal);

    if(res == -1){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(0, res);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}

int nuevo_token_ident(ListaTokens *lt, TablaIdentificadores *ti, char *ident){
    if(lt == NULL || ti == NULL || ident == NULL)
        return -1;
    
    int pos = insertar_tabla_identificadores(ti, ident);

    if(pos == -1){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(1, pos);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}

int nuevo_token_real(ListaTokens *lt, TablaReales *tr, char *num){
    if(lt == NULL || tr == NULL || num == NULL){
        return -1;
    }

    

}



int busquedaBinaria(const char *array, int l, int r, char *objetivo){
    if(l > r){
        return -1;
    }

    int m = (l + r)/2;
    int valCmp = strcmp(array[m], objetivo);
    if(valCmp == 0){
        return m;
    }else if(valCmp < 1){
        return busquedaBinaria(array, m + 1, r, objetivo);
    }else{
        return busquedaBinaria(array, l, m - 1, objetivo);
    }
}
