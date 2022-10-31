#include <stdlib.h>
#include "lex.yy.h"
#include "tablas.h"
#include "tokens.h"
int main(int argc, char *argv[]){
    char *archivoEntrada = NULL;
    if(argc > 1){
        archivoEntrada = argv[1];
    }else{
        return 1;
    }

    TablaReales *tr = nueva_tabla();
    TablaCadenas *tc = nueva_tabla();
    TablaIdentificadores *ti = nueva_tabla_indentificadores();
    ListaTokens *lt = nueva_lista_tokens();
    analizadorLexico(archivoEntrada, tr, tc, ti, lt);
    imprimir_tabla(tr);
    imprimir_tabla(tc);
    imprimir_tabla_identificadores(ti);
    imprimir_lista_tokens(lt);
    return 0;
}