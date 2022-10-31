#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablas.h"
#define CAPACIDAD_INICIAL 100
Tabla *nueva_tabla(){
    Tabla *nuevaTabla = (Tabla*) malloc(sizeof(Tabla));
    
    if(nuevaTabla == NULL){
        printf("No se pudo reservar la memoria solicitada");
        return NULL;
    }   

    char **nuevoArreglo = (char**)malloc(sizeof(char*) * CAPACIDAD_INICIAL);
    for(int i = 0; i < CAPACIDAD_INICIAL; i++){
        nuevoArreglo[i] = 0;
    }
    
    nuevaTabla -> arreglo = nuevoArreglo;
    nuevaTabla -> capacidad = CAPACIDAD_INICIAL;
    nuevaTabla -> tamanio = 0;
    return nuevaTabla;
}

int insertar_tabla(Tabla *t, char* cadena){
    if(t == NULL)
        return -1;
    
    if(cadena == NULL){
        return -1;
    }

    if( t->tamanio == t->capacidad){
        char **nuevoArreglo = (char**)malloc(sizeof(char*) * (t->capacidad + CAPACIDAD_INICIAL));
        if(nuevoArreglo == NULL)
            return -1;

        for(int i = 0; i < (t->capacidad + CAPACIDAD_INICIAL); i++){
            nuevoArreglo[i] = 0;
        }

        char **viejoArreglo = t->arreglo;
        //Se copian los elementos de un arreglo a otro
        for(int i = 0; i < t->tamanio; i++){
            nuevoArreglo[i] = viejoArreglo[i];
        }
        free(viejoArreglo);
        t->arreglo = nuevoArreglo;
        t->capacidad = t->capacidad + CAPACIDAD_INICIAL;
    }
    
    char *nuevaCadena = strdup(cadena);
    char **arregloCadenas = t->arreglo;
    arregloCadenas[t->tamanio] = nuevaCadena;
    t->tamanio++;
    return t->tamanio - 1;
}

void imprimir_tabla(Tabla *t){
    int tamanio = t->tamanio;
    printf("Pos  |  valor\n");
    for(int i = 0; i < tamanio; i++){
        char *cadenaActual = t->arreglo[i];
        printf("%d,   %s \n", i, cadenaActual);
    }
    printf("\n");
}

TablaIdentificadores *nueva_tabla_indentificadores(){
    TablaIdentificadores *nuevaTabla = (TablaIdentificadores*) malloc(sizeof(TablaIdentificadores));
    
    if(nuevaTabla == NULL){
        printf("No se pudo reservar la memoria solicitada");
        return NULL;
    }   

    Identificador *nuevoArreglo = (Identificador*)malloc(sizeof(Identificador) * CAPACIDAD_INICIAL);
    for(int i = 0; i < CAPACIDAD_INICIAL; i++){
        nuevoArreglo[i].nombre = 0;
        nuevoArreglo[i].tipo = -1;
    }
    
    nuevaTabla -> arreglo = nuevoArreglo;
    nuevaTabla -> capacidad = CAPACIDAD_INICIAL;
    nuevaTabla -> tamanio = 0;
    return nuevaTabla;
}

int insertar_tabla_identificadores(TablaIdentificadores *t, char* nombre){
    if(t == NULL)
        return -1;
    
    if(nombre == NULL){
        return -1;
    }

    if(t->tamanio == t->capacidad){
        Identificador *nuevoArreglo = (Identificador*)malloc(sizeof(Identificador) * (t->capacidad + CAPACIDAD_INICIAL));
        if(nuevoArreglo == NULL)
            return -1;

        for(int i = 0; i < (t->capacidad + CAPACIDAD_INICIAL); i++){
            nuevoArreglo[i].nombre = NULL;
            nuevoArreglo[i].tipo = -1;
        }

        Identificador *viejoArreglo = t->arreglo;
        //Se copian los elementos de un arreglo a otro
        for(int i = 0; i < t->tamanio; i++){
            nuevoArreglo[i] = viejoArreglo[i];
        }
        free(viejoArreglo);
        t->arreglo = nuevoArreglo;
        t->capacidad = t->capacidad + CAPACIDAD_INICIAL;
    }

    for(int i = 0; i < t->tamanio; i++){
        if(strcmp(nombre, t->arreglo[i].nombre) == 0){
            return i;
        }
    }

    Identificador *identificadoresActuales = t->arreglo;
    int siguienteIndice = t->tamanio;
    char * copiaNombre = strdup(nombre);

    identificadoresActuales[siguienteIndice].nombre = copiaNombre;
    identificadoresActuales[siguienteIndice].tipo = -1;
    t->tamanio++;
    return siguienteIndice;
}

void imprimir_tabla_identificadores(TablaIdentificadores *t){
    int tamanio = t->tamanio;
    printf("Pos  |  nombre  |   tipo\n");
    for(int i = 0; i < tamanio; i++){
        char *nombre = t->arreglo[i].nombre;
        int tipo = t->arreglo[i].tipo;
        printf("%d,   %s    %d\n", i, nombre, tipo);
    }
    printf("\n");
}
