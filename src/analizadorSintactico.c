/*
Autores: Ricardo López Becerra, Diego Ignacio Nuñez Hernández
Fecha de creación: 1/12/2022

En este archivo se define el analizador Sintáctico Descendente Recursivo.
*/

#include <stdio.h>
#include "tokens.h"

//Prototipos de las funciones
void avanzar();
void analizadorSintactico(ListaAtomos* la, FILE *archivoSalida);
void Program();
void otraFunc();
void Func();
void Param();
void otroParam();
void Cuerpo();
void Decl();
void D();
void Tipo();
void K();
void Q();
void N();
void C();
void A();
void AP();
void E();
void EP();
void T();
void TP();
void F();
void R();
void RP();
void V();
void VP();
void VPP();
void VPPP();
void P();
void listaP();
void W();
void I();
void IP();
void J();
void Y();
void X();
void Z();
void H();
void CP();
void OP();
void U();
void Devuelve();
void valor();
void Llama();
void arg();
void otroArg();

// Variables globales
NodoAtomo* actual;
int ubicacion;
FILE *erroresSintacticos;

/*
    Función en donde se manda a llamar a la fucnión del símbolo inicial de la gramática y
    se inicializa el apuntador a la lista de átomos y el archivo de errores.
    Si el apuntador llega al final de la lista (es nulo) significa que no hay errores
    sintácticos.
*/
void analizadorSintactico(ListaAtomos* la, FILE *archivoSalida){
    erroresSintacticos = fopen("erroresSintacticos.txt", "w");
    actual = la->head;
    ubicacion = 1;
    Program();
    if(actual == NULL){
        fprintf(archivoSalida,"EL ARCHIVO ES SINTACTICAMENTE CORRECTO\n");
    } else {
        fprintf(archivoSalida,"EL ARCHIVO ES SINTACTICAMENTE INCORRECTO\n");
    }
}

/*
    Función que apunta al nodo siguiente de la lista de átomos e
    incrementa la ubicacion.
*/
void avanzar(){
    actual=actual->next;
    ubicacion++;
}

// Funciones de los no-terminales de la gramática 
void Program(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Func();
        otraFunc();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba la declaracion de una funcion\n",ubicacion);
    }
}

void otraFunc(){
    if(actual==NULL){
        return;
    }else if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Func();
        otraFunc();
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba la declaracion de una funcion o el fin del archivo\n",ubicacion);
    }
}

void Func(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Tipo();
        if(actual->info == 'i'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
            return;
        }
        if(actual->info == '('){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '('\n",ubicacion);
            return;
        }
        Param();
        if(actual->info==')'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ')'\n",ubicacion);
            return;
        }
        if(actual->info=='{'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '{'\n",ubicacion);
            return;
        }
        Cuerpo();
        if(actual->info=='}'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '}'\n",ubicacion);
            return;
        }
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un tipo de dato\n",ubicacion);
    }
}

void Param(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Tipo();
        if(actual->info == 'i'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
            return;
        }
        otroParam();
    } else if(actual->info == ')') {
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba tipo de dato del parametro\n",ubicacion);
    }
}

void otroParam(){
    if(actual->info==','){
        avanzar();
        Tipo();
        if(actual->info == 'i'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
            return;
        }
        otroParam();
    } else if(actual->info==')'){
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba tipo de dato del parametro\n",ubicacion);
    }
}

void Cuerpo(){
    if(actual->info=='i'||actual->info=='}'||actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'||actual->info=='c'||actual->info=='w'||actual->info=='f'||actual->info=='j'||actual->info=='h'||actual->info=='z'||actual->info=='['){
        Decl();
        listaP();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un cuerpo de funcion o } o [\n",ubicacion);
    }
}

void Decl(){
    if(actual->info=='i'||actual->info=='}'||actual->info=='c'||actual->info=='w'||actual->info=='f'||actual->info=='j'||actual->info=='h'||actual->info=='z'||actual->info=='['){
        return;
    } else if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        D();
        Decl();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba una declaracion\n",ubicacion);
    }
}

void D(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Tipo();
        K();
        if(actual->info==';'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ';'\n",ubicacion);
            return;
        }
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un tipo de dato\n",ubicacion);
    }
}

void Tipo(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un tipo de dato\n",ubicacion);
    }
}

void K(){
    if(actual->info=='i'){
        avanzar();
        Q();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
    }
}

void Q(){
    if(actual->info==';'){
        return;
    } else if(actual->info=='=') {
        avanzar();
        N();
        C();
    } else if(actual->info==','){
        avanzar();
        K();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ; o = o ,\n",ubicacion);
    }
}

void N(){
    if (actual->info=='n'||actual->info=='r'||actual->info=='s'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Sentencia una constante numerica o cadena\n",ubicacion);
    }
}

void C(){
    if(actual->info==';'){
        return;
    } else if(actual->info==','){
        avanzar();
        K();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba , o ;\n",ubicacion);
    }
}

void A(){
    if (actual->info=='i'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba i\n",ubicacion);
        return;
    }
    if(actual->info=='='){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba =\n",ubicacion);
        return;
    }
    AP();
    if(actual->info==';'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ;\n",ubicacion);
    }
}

void AP(){
    if(actual->info=='s'){
        avanzar();
    } else if(actual->info=='('||actual->info=='i'||actual->info=='n'||actual->info=='r'||actual->info=='['){
        E();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Sentencia de asignación incorrecta\n",ubicacion);
    }
}

void E(){
    if(actual->info=='('||actual->info=='i'||actual->info=='n'||actual->info=='r'||actual->info=='['){
        T();
        EP();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador, una constante numerica, ( o ]\n",ubicacion);
    }
}

void EP(){
    if(actual->info=='+'||actual->info=='-'){
        avanzar();
        T();
        EP();
    } else if(actual->info==';'||actual->info==')'){
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba + o - o ; o )\n",ubicacion);
    }
}

void T(){
    if(actual->info=='('||actual->info=='i'||actual->info=='n'||actual->info=='r'||actual->info=='['){
        F();
        TP();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador, una constante numerica, ( o ]\n",ubicacion);
    }
}

void TP(){
    if(actual->info=='*'||actual->info=='/'||actual->info=='\\'||actual->info=='%'||actual->info=='^'){
        avanzar();
        F();
        TP();
    } else if(actual->info==';'||actual->info==')'||actual->info=='+'||actual->info=='-'){
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ';', ')', '+', '-', '*', '/, '\\', '%%' o '^'\n",ubicacion);
    }
}

void F(){
    if(actual->info=='('){
        avanzar();
        E();
        if(actual->info==')'){
            avanzar();
            return; 
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba )\n",ubicacion);
        }
    } else if(actual->info=='i'||actual->info=='n'||actual->info=='r'){
        avanzar();
    } else if(actual->info=='['){
        Llama();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ( o [ o identificador o constante numerica\n",ubicacion);
    }
}

void R(){
    if(actual->info=='i'){
        avanzar();
        RP();
        V();
    } else if(actual->info=='n'){
        avanzar();
        RP();
        VP();
    } else if(actual->info=='r'){
        avanzar();
        RP();
        VPP();
    } else if(actual->info=='s'){
        avanzar();
        RP();
        VPPP();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba identificador, constante numerica o cadena\n",ubicacion);
    }
}

void RP(){
    if(actual->info=='>'||actual->info=='<'||actual->info=='l'||actual->info=='e'||actual->info=='d'||actual->info=='u'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba operador relacional",ubicacion);
    }
}

void V(){
    if(actual->info=='i'||actual->info=='n'||actual->info=='r'||actual->info=='s'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba identificador, constante numerica o cadena\n",ubicacion);
    }
}

void VP(){
    if(actual->info=='i'||actual->info=='n'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba identificador o constante numerica\n",ubicacion);
    }
}

void VPP(){
    if(actual->info=='i'||actual->info=='r'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba identificador o constante numerica\n",ubicacion);
    }
}

void VPPP(){
    if(actual->info=='i'||actual->info=='s'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba identificador o cadena\n",ubicacion);
    }
}

void P(){
    if(actual->info=='i'){
        A();
    } else if(actual->info=='f'){
        I();
    } else if(actual->info=='h'){
        H();
    } else if(actual->info=='w'){
        W();
    } else if(actual->info=='j'){
        J();
    } else if(actual->info=='['){
        Llama();
    } else if(actual->info=='z'){
        Devuelve();
    } else if(actual->info=='c'){
        avanzar();
        if(actual->info==';'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ;\n",ubicacion);
        }
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Proposicion incorrecta\n",ubicacion);
    }
}

void listaP(){
    if(actual -> info == '}' || actual -> info == ':' || actual -> info == 't' || actual -> info == 'a' || actual -> info == 'o' || actual -> info == 'q'){
        return;
    }else if(actual -> info == 'i' || actual -> info == 'c' || actual -> info == 'w' || actual -> info == 'f' || actual -> info == 'j' || actual -> info == 'h' || actual -> info == 'z' || actual -> info == '['){
        P();
        listaP();
    }

}

void W(){
    if(actual -> info == 'w'){
        avanzar();
        
        if(actual -> info == '('){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba (\n",ubicacion);
        }
        
        R();
        
        if(actual -> info == ')'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba )\n",ubicacion);
        }

        if(actual -> info == 'm'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'make'\n",ubicacion);
        }

        if(actual -> info == '{'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba {\n",ubicacion);
        }

        listaP();

        if(actual -> info == '}'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba }\n",ubicacion);
        }
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'loop'\n",ubicacion);
    }
}

void I(){
    if(actual -> info == 'f'){
        avanzar();
        
        if(actual -> info == '('){
            avanzar();

        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba (\n",ubicacion);
        }

        R();

        if(actual -> info == ')'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba )\n",ubicacion);
        }

        listaP();
        IP();   
        if(actual -> info == ':'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba :\n",ubicacion);
        }
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'evaluate'\n",ubicacion);
    }
    
}

void IP(){
    if(actual -> info == 't'){
        avanzar();
        listaP();
    }else if(actual -> info == ':'){
        return;
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba : o 'instead'\n",ubicacion);
    }
}

void J(){
    if(actual -> info == 'j'){
        avanzar();
        if(actual -> info == '('){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba '('\n", ubicacion);
        }

        Y();
        X();
        Z();

        if(actual -> info == '{'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba '{'\n", ubicacion);
        }

        listaP();

        if(actual -> info == '}'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba '}'\n", ubicacion);
        }
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'repeat'\n", ubicacion);
    }
    
}

void Y(){
    if(actual -> info == 'i'){
        avanzar();
        
        if(actual -> info == '='){
            avanzar();
        } else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba =\n",ubicacion);
        }

        E();

        if(actual -> info == ';'){
            avanzar();
        } else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ;\n",ubicacion);
        }
    }else if(actual -> info == ';'){
        avanzar();
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba identificador o ;\n",ubicacion);
    }
}

void X(){
    if(actual -> info == 'i' || actual -> info == 'n' || actual -> info == 'r' || actual -> info == 's'){
        R();
        if (actual -> info == ';'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ';'\n",ubicacion);
        }
    }else if(actual -> info == ';'){
        avanzar();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ',', entero, real, cadena o identificador\n",ubicacion);
    }
}

void Z(){
    if(actual -> info == 'i'){
        avanzar();
        if(actual -> info == '='){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '='\n",ubicacion);
        }
        E();
        if(actual -> info == ')'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ')'\n",ubicacion);
        }
    } else if(actual -> info == ')'){
        avanzar();
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador o un ')'\n",ubicacion);
    }
}

void H(){
    if(actual -> info == 'h'){
        avanzar();
        
        if(actual -> info == '('){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '('\n",ubicacion);
        }

        if(actual -> info == 'i'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
        }

        if(actual -> info == ')'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ')'\n",ubicacion);
        }

        if(actual -> info == '{'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '{'\n",ubicacion);
        }

        CP();
        OP();

        if(actual -> info == '}'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '}'\n",ubicacion);
        }

    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un 'select'\n",ubicacion);
    }
    
}

void CP(){
    if(actual -> info == 'a'){
        avanzar();
        if(actual -> info == 'n'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un entero\n",ubicacion);
        }

        if(actual -> info == ':'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ':'\n",ubicacion);
        }

        listaP();
        U();
        CP();

    }else if (actual -> info == '}' || actual ->info == 'o'){
        return;
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '}' o un 'other'\n",ubicacion);
    }
}

void OP(){
    if(actual -> info == 'o'){
        avanzar();
        if(actual -> info == ':'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ':'\n",ubicacion);
        }
        listaP();
    }else if(actual -> info == '}'){
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'other' o '}'\n",ubicacion);
    }
    return;
}

void U(){
    if(actual -> info == 'q'){
        avanzar();
    } else if(actual -> info == '}' || actual -> info == 'a' || actual -> info == 'o'){
        return;
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'stop', 'case', 'other' o '}'\n",ubicacion);
    }
    return;
    
}

void Devuelve(){
    if(actual -> info == 'z'){
        avanzar();
        
        if(actual -> info == '('){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '('\n",ubicacion);
        }
        
        valor();
        
        if(actual -> info == ')'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ')'\n",ubicacion);
        }

        if(actual -> info == ';'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ';'\n",ubicacion);
        }
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba 'throw'\n",ubicacion);
    }
    return;
}

void valor(){
    if(actual -> info == 'i' || actual -> info == 'n' || actual -> info == 'r' || actual -> info == 's'){
        V();
    }else if(actual -> info == ')'){
        return;
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba una expresion o un )\n",ubicacion);
    }
    return;
}

void Llama(){
    if(actual -> info == '['){
        avanzar();
        
        if(actual -> info == 'i'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
        }
        
        if(actual -> info == '('){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '('\n",ubicacion);
        }
        
        arg();

        if(actual -> info == ')'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ')'\n",ubicacion);
        }

        if(actual -> info == ']'){
            avanzar();
        }else{
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ']'\n",ubicacion);
        }
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba la llamada a una función\n",ubicacion);
    } 

    return;
}

void arg(){
    if(actual -> info == ')'){
        return;
    }else if(actual -> info == 'i' || actual -> info == 'n' || actual -> info == 'r' || actual -> info == 's'){
        V();
        otroArg();
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador, numero, real cadena o ')'\n",ubicacion);
    }
    return;
}

void otroArg(){
    if(actual -> info == ','){
        V();
        otroArg();
    }else if(actual -> info == ')'){
        return;
    }else{
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba ')' o ',' \n",ubicacion);
    }
    return;
}