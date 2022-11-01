#include <stdlib.h>
#include <stdio.h>
#include "lex.yy.h"
#include "tablas.h"
#include "tokens.h"
#include <stdio.h>
int main(int argc, char *argv[]){
    FILE *archivoEntrada = NULL;
    FILE *archivoSalida = fopen("tablas-generadas.txt", "w");
    archivoSalida = freopen("tablas-generadas.txt","a",archivoSalida);
    if(argc > 1){
        archivoEntrada = fopen(argv[1], "r");
    }else{
        return 1;
    }

    TablaReales *tr = nueva_tabla();
    TablaCadenas *tc = nueva_tabla();
    TablaIdentificadores *ti = nueva_tabla_indentificadores();
    ListaTokens *lt = nueva_lista_tokens();
    analizadorLexico(archivoEntrada, tr, tc, ti, lt);
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