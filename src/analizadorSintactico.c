#include <stdio.h>
#include "tokens.h"
NodoAtomo* actual;
int ubicacion;
FILE *erroresSintacticos;
analizadorSintactico(ListaAtomos* la, FILE *archivoSalida){
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
//LIMPIARMEMORIA
void avanzar(){
    actual=actual->next;
    ubicacion++;
}

void Program(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Func();
        otraFunc();
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba la declaracion de una funcion\n",ubicacion);
    }
    return;
}

void otraFunc(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Func();
        otraFunc();
    } else if(actual==NULL){
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba la declaracion de una funcion o el fin del archivo\n",ubicacion);
    }
    return;
}

void Func(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Tipo();
        if(actual->inf == 'i'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
        }

        if(actual->info == '('){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '('\n",ubicacion);
        }

        Param();
        
        if(actual->info==')'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un ')'\n",ubicacion);
        }

        if(actual->info=='{'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '{'\n",ubicacion);
        }
        
        Cuerpo();
        
        if(actual->info=='}'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un '}'\n",ubicacion);
        }
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un tipo de dato\n",ubicacion);
    }
}

void Param(){
    if(actual->info=='b'||actual->info=='g'||actual->info=='#'||actual->info=='y'||actual->info=='x'){
        Tipo();
        if(actual->inf == 'i'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
        }
        otroParam();
    } else if(actual->inf == ')') {
        return;
    } else {
        fprintf(erroresSintacticos,"ERROR(%d): Se esperaba tipo de dato del parametro\n",ubicacion);
    }
    return;
}

void otroParam(){

}

void Cuerpo(){

}

void Decl(){

}

void D(){

}

void Tipo(){

}

void K(){

}

void Q(){

}

void N(){
    
}

void C(){
    
}

void A(){
    
}

void AP(){
    
}

void E(){
    
}

void EP(){
    
}

void T(){
    
}

void TP(){
    
}

void F(){
    
}

void R(){
    
}

void RP(){
    
}

void V(){
    
}

void VP(){
    
}

void VPP(){
    
}

void VPPP(){
    
}

void P(){
    
}

void listaP(){
    
}

void W(){
    
}

void I(){
    
}

void IP(){
    
}

void J(){
    
}

void Y(){
    
}

void X(){
    
}

void Z(){
    
}

void H(){
    
}

void CP(){
    
}

void OP(){
    
}

void U(){
    
}

void Devuelve(){
    
}

void valor(){
    
}

void Llama(){
    
}

void arg(){
    
}

void otroArg(){
    
}