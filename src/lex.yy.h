#ifndef LEX_YY_H
#define LEX_YY_H
#include "tablas.h"
#include "tokens.h"
void analizadorLexico(FILE* archivoEntrada, TablaReales *tr, TablaCadenas *tc, TablaIdentificadores *ti, ListaTokens *lt);
#endif