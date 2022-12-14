/*
    Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
    Fecha de creación: 29/10/2022
    Definición de las estructuras para representar a los identificadores,
    la tabla de identificadores y la tabla de constantes. Además se
    definen las funciones que se ejecutan sobre ellas.
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

typedef Tabla TablaReales;
typedef Tabla TablaCadenas;

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

Tabla *nueva_tabla();
int insertar_tabla(Tabla *tabla, char* cadena);
void imprimir_tabla(Tabla *t, FILE *archivoSalida);

TablaIdentificadores *nueva_tabla_indentificadores();
int insertar_tabla_identificadores(TablaIdentificadores *t, char* nombre);
void imprimir_tabla_identificadores(TablaIdentificadores *t, FILE *archivoSalida);

#endif