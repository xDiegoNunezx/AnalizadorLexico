/*
Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
Fecha de creación: 1/12/2022

En este archivo se define el prototipo de la función encargada de iniciar
el análisis sintáctico.
*/
#ifndef ANALIZADOR_SINTACTICO_H
#define ANALIZADOR_SINTACTICO_H
#include <stdio.h>
#include "tokens.h"
void analizadorSintactico(ListaAtomos* la, FILE *archivoSalida);
#endif