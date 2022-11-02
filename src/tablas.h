/*
    Definición de las structuras para representar tablas de constantes, 
    Tabla de indentificadores e identificadores así como las funciones 
    que funcionan sobre ellas.

*/

#ifndef TABLAS_H
#define TABLAS_H
#include <stdio.h>

/*
    Tabla de contantes.
*/
typedef struct Tabla{
    int tamanio;
    int capacidad;
    char **arreglo;
} Tabla;

/*
    Identificador con nombre y tipo.
*/
typedef struct Identificador{
    char* nombre;
    int tipo;
}Identificador;

/*
    Tabla de identificadores.
*/
typedef struct TablaIdentificadores{
    int tamanio;
    int capacidad;
    Identificador *arreglo;
}TablaIdentificadores;


typedef Tabla TablaReales;
typedef Tabla TablaCadenas;

Tabla *nueva_tabla();
int insertar_tabla(Tabla *tabla, char* cadena);
void imprimir_tabla(Tabla *t, FILE *archivoSalida);

TablaIdentificadores *nueva_tabla_indentificadores();
int insertar_tabla_identificadores(TablaIdentificadores *t, char* nombre);
void imprimir_tabla_identificadores(TablaIdentificadores *t, FILE *archivoSalida);

#endif