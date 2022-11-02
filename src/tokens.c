/*
    Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
    Fecha de creación: 30/10/2022

    En este archivo se definen las acciones necesarias para crear la 
    lista de tokens generada por el analizador. Se definen funciones
    para crear cada tipo de token.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tokens.h"
#include "tablas.h"

const char *palabrasReservadas[17] = {"alternative", "big", "evaluate",
        "instead", "large", "loop", "make", "number", "other", "real",
        "repeat", "select", "small", "step", "stop", "symbol", "throw"};

const char *TablaOperadoresA[7] = {"+","-","*","/","%","\\","^"};

const char *TablaOperadoresR[6] = {"<",">","<=",">=","==","!="};



int busquedaBinaria(const char **array, int l, int r, char *objetivo);
int octaltodecimal(int octal);

/*
    Crea un nuevo objeto de tipo Token
    clase: La clase del token a crear.
    valor: El valor del token.
*/
Token *nuevo_Token(int clase, int valor){
    Token *nuevoToken = (Token*)malloc(sizeof(Token));
    if(nuevoToken == NULL){
        return NULL;
    }
    nuevoToken->clase = clase;
    nuevoToken->valor = valor;
    return nuevoToken;
}
/*
    Función que crea un nuevo nodo de la lista ligada de Tokens
    valor: Apuntador a objeto de tipo token a almacenar en el nodo.
*/
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
/*
    Crea una nueva lista ligada de Tokens 
*/
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
/*
    Inserta un nuevo token a una lista ligada de Tokens.
    lt: Lista ligada donde insertar el token.
    nuevoToken: Token a insertar en la lista ligada.
*/
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
        lt->tail = nuevoNodo;
        return 0;
    }

    lt->tail->next = nuevoNodo;
    nuevoNodo->prev = lt->tail;
    lt->tail = nuevoNodo;
    return 0;
}

/*
    Función que imprime una lista de tokens a un archivo.
    lt: Lista de tokens a imprimir.
    archivoSalida: Objeto de tipo FILE que representa el archivo donde se 
    imprimirá la lista.
*/
void imprimir_lista_tokens(ListaTokens *lt, FILE *archivoSalida){
    NodoToken *nodoActual = lt -> head;
    fprintf(archivoSalida, "(clase   ,   valor) \n");
    while(nodoActual){
        fprintf(archivoSalida, "(%d     ,      %d) \n", nodoActual->info->clase, nodoActual->info->valor);
        nodoActual = nodoActual->next;
    }
    fprintf(archivoSalida, "\n");
}

/*
    Función que cambia un número en representación octal a decimal.
    octal: Número en representación octal.
*/
int octaltodecimal(int octal){
    int decimalnumber = 0, i = 0;

    while (octal != 0) {

        decimalnumber
            = decimalnumber + (octal % 10) * pow(8, i++);
        octal = octal / 10;
    }

    return decimalnumber;
}
/*
    Función que realiza busqueda binaria en un arreglo de cadenas.
    Devuelve el índice de la cadena en caso de ser encontrada. De no ser
    así devuelve -1.
    array: Arreglo de apuntadores a cadenas.
    l: Indice que es cota inferior inclusiva de la búsqueda.
    r: Indice que es cota superior inclusiva de la búsqueda.
    objetivo: Apuntador a la cadena buscada.
*/
int busquedaBinaria(const char **array, int l, int r, char *objetivo){
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

/*
    Crea un token de clase 0 (Palabra reservada). Utiliza busqueda binaria para encontrar
    la posición de la palabra reservada.
    lt: Lista donde agregar el token.
    pal: Cadena con la palabra reservada a buscar.
*/
int nuevo_token_pal_res(ListaTokens* lt, char * pal){
    if(lt == NULL){
        return -1;
    }
    int res = busquedaBinaria(palabrasReservadas, 0, 16, pal);
    if(res == -1){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(0, res);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}
/*
    Crea un token de clase 1 (Identificador). Inserta al identificador en la tabla 
    de indeitificadores. Si es nuevo, utiliza su nueva posición asignada; si es repetido,
    utiliza la posición existente.
    lt: Lista donde agregar el token.
    ti: Tabla de identificadores donde buscar y agregar.
    ident: Cadena con el nombre del identificador.
*/
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

/*
    Crea un token de clase 2 (Constante entera) a partir de un número decmal.
    El valor del token es el mismo decimal.
    lt: Lista donde agregar el token.
    num: Cadena que representa al número decimal.
*/
int nuevo_token_decimal(ListaTokens *lt, char *num){
    int n = atoi(num);
    Token *nuevoToken = nuevo_Token(2, n);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}

/*
    Crea un token de clase 2 (Constante entera). El valor del token es el valor
    octal obtenido representado de manera decimal.
    lt: Lista donde agregar el token.
    num: Cadena que representa al número octal.
*/

int nuevo_token_octal(ListaTokens *lt, char *num){
    char *numLimpio = num + 1;
    int n = atoi(numLimpio);
    int valorDecimal = octaltodecimal(n);

    Token *nuevoToken = nuevo_Token(2, valorDecimal);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}

/*
    Crea un token de clase 3 (Constante real). Inserta al identificador en la tabla 
    de indeitificadores y utiliza su nueva posición asignada
    lt: Lista donde agregar el token.
    tr: Tabla de constantes reales donde agregar la componente léxica.
    num: Cadena que representa al número real.
*/
int nuevo_token_real(ListaTokens *lt, TablaReales *tr, char *num){
    if(lt == NULL || tr == NULL || num == NULL){
        return -1;
    }
    int pos = insertar_tabla(tr, num);

    if(pos == -1){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(3, pos);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}

/*
    Crea un token de clase 4 (Constante cadena). El valor del token es la posición 
    de la cadena en la tabla de constantes cadena.
    lt: Lista donde agregar el token.
    Cadena: Cadena que representa la constante cadena a partir de la cual se creará el token.
*/
int nuevo_token_cadena(ListaTokens* lt, Tabla *tc,char *cadena) {
    if(lt == NULL){
        return -1;
    }

    int pos = insertar_tabla(tc,cadena);

    if(pos == -1){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(4, pos);
    agregar_lista_tokens(lt, nuevoToken);

    return 0;
}
/*
    Crea un token de clase 5 (Símbolo especial). El valor del token es el código
    ASCII del símbolo especial.
    lt: Lista donde agregar el token.
    simbolo: Cadena que representa al símbolo especial. Debe tener solo un caracter.
*/

int nuevo_token_simbolo(ListaTokens *lt, char *simbolo){
    Token *nuevoToken = nuevo_Token(5, *simbolo);
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}

/*
    Crea un token de clase 6 (Operador aritmético). El valor del token es el código
    ASCII del operador.
    lt: Lista donde agregar el token.
    cadena: Cadena que representa al operador. Debe tener solo un caracter.
*/
int nuevo_token_operadorA(ListaTokens *lt, char *cadena){
    if(lt == NULL){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(6, *cadena);
    agregar_lista_tokens(lt, nuevoToken);

    return 0;
    
}
/*
    Crea un token de clase 7 (Operador relacional). Utiliza busqueda lineal para encontrar
    la posición de la palabra reservada y utiliza este valor como valor del token.
    lt: Lista donde agregar el token.
    cadena: Cadena con el operador aritmético a insertar.
*/
int nuevo_token_operadorR(ListaTokens *lt, char *cadena){
    if(lt == NULL){
        return -1;
    }
    
    int pos = -1;
    for (int i = 0; i < 6; i++){
        if(strcmp(TablaOperadoresR[i], cadena) == 0){
            pos = i;
            break;
        }
    }

    if(pos == -1){
        return -1;
    }

    Token *nuevoToken = nuevo_Token(7, pos);
    agregar_lista_tokens(lt, nuevoToken);

    return 0;   
}

/*
    Crea un token de clase 8 (Operador de asignación). Utiliza el valor ASCII del
    símbolo "=" para el campo valor del token.
    lt: Lista donde agregar el token.
*/
int nuevo_token_asignacion(ListaTokens *lt){
    Token *nuevoToken = nuevo_Token(8, '=');
    agregar_lista_tokens(lt, nuevoToken);
    return 0;
}