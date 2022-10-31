#ifndef TABLAS_H
#define TABLAS_H



typedef struct Tabla{
    int tamanio;
    int capacidad;
    char **arreglo;
} Tabla;

typedef struct Identificador{
    char* nombre;
    int tipo;
}Identificador;

typedef struct TablaIdentificadores{
    int tamanio;
    int capacidad;
    Identificador *arreglo;
}TablaIdentificadores;


typedef Tabla TablaReales;
typedef Tabla TablaCadenas;

Tabla *nueva_tabla();
int insertar_tabla(Tabla *tabla, char* cadena);
void imprimir_tabla(Tabla *t);

TablaIdentificadores *nueva_tabla_indentificadores();
int insertar_tabla_identificadores(TablaIdentificadores *t, char* nombre);
void imprimir_tabla_identificadores(TablaIdentificadores *t);

#endif