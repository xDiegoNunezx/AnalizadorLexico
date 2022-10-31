#ifndef LEX_YY_H
#define LEX_YY_H
#include "tablas.h"
#include "tokens.h"
int analizadorLexico(char* archivoEntrada, TablaReales *tr, TablaCadenas *tc, TablaIdentificadores *ti, ListaTokens *lt);
#endif