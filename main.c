#include <stdlib.h>
#include "lex.yy.h"
#include "tablas.h"
void main(int argc, char *argv[]){
    char *archivoEntrada = NULL;
    if(argc > 1){
        archivoEntrada = argv[1];
    }

    TablaReales *tr = nueva_tabla();
    TablaCadenas *tc = nueva_tabla();
    TablaIdentificadores *ti = nueva_tabla_indentificadores();

    analizadorLexico(archivoEntrada, tr, tc, ti);
    imprimir_tabla(tr);
    imprimir_tabla(tc);
    imprimir_tabla_identificadores(ti);
}