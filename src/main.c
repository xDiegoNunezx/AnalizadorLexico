/*
Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
Fecha de creación: 30/10/2022

Analizador léxico que reconoco las clases solicitadas.

Punto de acceso al programa. El programa debe recibir un parametro al ser corrido especificando el archivo 
a analizar. Si no se pasa ningún archivo al programa, este detiene su ejecución. Aquí se inicializan las
tablas de símbolos y la lista ligada de tokens. Desde este punto también se inicial el analisis y se imprimen
las tablas de símbolos al terminar.
*/

#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "tablas.h"
#include "tokens.h"

int main(int argc, char *argv[]){
    FILE *archivoEntrada = NULL;
    FILE *archivoSalida = fopen("tablas-generadas.txt", "w");
    archivoSalida = freopen("tablas-generadas.txt","a",archivoSalida);
    if(argc > 1){
        archivoEntrada = fopen(argv[1], "r");
        if(archivoEntrada == NULL){
            return -1;
        }
    }else{
        return 1;
    }

    TablaReales *tr = nueva_tabla();
    TablaCadenas *tc = nueva_tabla();
    TablaIdentificadores *ti = nueva_tabla_indentificadores();
    ListaTokens *lt = nueva_lista_tokens();
    analizadorLexico(archivoEntrada, tr, tc, ti, lt);
    ListaAtomos *la = nueva_lista_atomos(lt);
    analizadorSintactico(la, archivoSalida);
    fprintf(archivoSalida, "===Cadena de atomos=== \n");
    imprimir_lista_atomos(la, archivoSalida);
    fprintf(archivoSalida, "===Tabla de reales=== \n");
    imprimir_tabla(tr, archivoSalida);
    fprintf(archivoSalida, "===Tabla de cadenas=== \n");
    imprimir_tabla(tc, archivoSalida);
    fprintf(archivoSalida, "===Tabla de identificadores=== \n");
    imprimir_tabla_identificadores(ti, archivoSalida);
    fprintf(archivoSalida, "===Lista de tokens producidos=== \n");
    imprimir_lista_tokens(lt, archivoSalida);
    
    return 0;
}