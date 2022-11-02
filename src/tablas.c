/*
Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
Fecha de creación: 29/10/2022

En este archivo se definen las funciones que pueden actuar sobre objetos de tipo Tabla y TablaIdenficadores
así como las funciones necesarias para la creación de estos objectos.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tablas.h"
#define CAPACIDAD_INICIAL 100

/*
Función que devuelve un objecto de tipo tabla. Las tablas tienen una capacidad de 
CAPACIDAD_INICIAL al crearse. Retorna un apuntador nulo si no es posible reservar 
la memoria necesaria.
*/
Tabla *nueva_tabla(){
    Tabla *nuevaTabla = (Tabla*) malloc(sizeof(Tabla));
    
    if(nuevaTabla == NULL){
        printf("No se pudo reservar la memoria solicitada");
        return NULL;
    }   

    char **nuevoArreglo = (char**)malloc(sizeof(char*) * CAPACIDAD_INICIAL);
    
    // Se limpia la memoria del arreglo dinámico interno a la tabla.
    for(int i = 0; i < CAPACIDAD_INICIAL; i++){
        nuevoArreglo[i] = NULL;
    }
    
    nuevaTabla -> arreglo = nuevoArreglo;
    nuevaTabla -> capacidad = CAPACIDAD_INICIAL;
    nuevaTabla -> tamanio = 0;
    return nuevaTabla;
}

/*
Inserta una cadena en un objeto de tipo tabla. La posición del objeto es su indice en el arreglo 
Devuelve -1 si la operacion no fue exitosa por en caso de que alguno de los apuntadores 
proporcionados sea nulo o en caso de que la tabla deba crecer y no se pueda reservar memoria
suficiente. Devuelve el indice del elemento insertado en caso de que la operación se realice 
exitosamente.
t: Apuntador a objeto de tipo Tabla
cadena: Apuntador a cadena (Componente léxica) a copiar e insertar el la tabla de componentes léxicas
*/
int insertar_tabla(Tabla *t, char* cadena){
    if(t == NULL)
        return -1;
    
    if(cadena == NULL){
        return -1;
    }
    /*
    Si la cantidad de elementos en el arreglo dinámico es igual a su capacidad, se reserva uno nuevo 
    con CAPACIDAD_INICIAL espacios extra, se copian los elemetos de un arreglo a otro y se libera la
    memoria del arreglo original.
    */
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
/*
    Función que imprime una tabla de tokens a un archivo.
    t: Apuntador a tabla de tokens a imprimir.
    archivoSalida: Apuntador a objeto de tipo FILE que representa
    el archivo donde se imprimirá la tabla.
*/
void imprimir_tabla(Tabla *t, FILE *archivoSalida){
    if(t == NULL){
        return;
    }
    int tamanio = t->tamanio;
    fprintf(archivoSalida, "Pos  |  valor\n\n");
    for(int i = 0; i < tamanio; i++){
        char *cadenaActual = t->arreglo[i];
        fprintf(archivoSalida, "%d     %s \n", i, cadenaActual);
    }
    fprintf(archivoSalida, "\n");
}

/*
Función que devuelve un objecto de tipo tablaIdentificadores. Las tablas tienen una capacidad de 
CAPACIDAD_INICIAL al crearse. Retorna un apuntador nulo si no es posible reservar 
la memoria necesaria.
*/

TablaIdentificadores *nueva_tabla_indentificadores(){
    TablaIdentificadores *nuevaTabla = (TablaIdentificadores*) malloc(sizeof(TablaIdentificadores));
    
    if(nuevaTabla == NULL){
        printf("No se pudo reservar la memoria solicitada");
        return NULL;
    }   

    Identificador *nuevoArreglo = (Identificador*)malloc(sizeof(Identificador) * CAPACIDAD_INICIAL);
    for(int i = 0; i < CAPACIDAD_INICIAL; i++){
        nuevoArreglo[i].nombre = NULL;
        nuevoArreglo[i].tipo = -1;
    }
    
    nuevaTabla -> arreglo = nuevoArreglo;
    nuevaTabla -> capacidad = CAPACIDAD_INICIAL;
    nuevaTabla -> tamanio = 0;
    return nuevaTabla;
}

/*
Inserta una cadena en un objeto de tipo tablaIdentificadores. La posición del objeto es su indice en el arreglo 
Devuelve -1 si la operacion no fue exitosa por en caso de que alguno de los apuntadores 
proporcionados sea nulo o en caso de que la tabla deba crecer y no se pueda reservar memoria
suficiente. Devuelve el indice del elemento insertado en caso de que la operación se realice 
exitosamente. En caso de que el identificador ya se encuentre en la tabla, devuelve el índice del
elemento.
t: Apuntador a un objeto de tipo TablaIdentificadores
nombre: Apuntador a cadena (Componente léxica) a copiar e insertar en la tabla de identificadores. Esta cadena
corresponde al nombre del identificador.
*/

int insertar_tabla_identificadores(TablaIdentificadores *t, char* nombre){
    if(t == NULL)
        return -1;
    
    if(nombre == NULL){
        return -1;
    }

    /*
    Búsqueda lineal del nuevo nombre de identificador en la lista de identificadores. Si es encontrado,
    devuelve el índice donde se encontró.
    */
    for(int i = 0; i < t->tamanio; i++){
        if(strcmp(nombre, t->arreglo[i].nombre) == 0){
            return i;
        }
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


    Identificador *identificadoresActuales = t->arreglo;
    int siguienteIndice = t->tamanio;
    char * copiaNombre = strdup(nombre);

    identificadoresActuales[siguienteIndice].nombre = copiaNombre;
    identificadoresActuales[siguienteIndice].tipo = -1;
    t->tamanio++;
    return siguienteIndice;
}
/*
    Función que imprime una tabla de identificadores a un archivo.
    t: Apuntador a tabla de identificadores a imprimir.
    archivoSalida: Apuntador a objeto de tipo FILE que representa
    el archivo donde se imprimirá la tabla.
*/
void imprimir_tabla_identificadores(TablaIdentificadores *t, FILE *archivoSalida){
    int tamanio = t->tamanio;
    fprintf(archivoSalida, "Pos  |  nombre  |   tipo\n\n");
    for(int i = 0; i < tamanio; i++){
        char *nombre = t->arreglo[i].nombre;
        int tipo = t->arreglo[i].tipo;
        fprintf(archivoSalida, "%d     %s         %d\n", i, nombre, tipo);
    }
    fprintf(archivoSalida,"\n");
}
