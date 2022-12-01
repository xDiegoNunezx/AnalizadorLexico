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
        if(actual->info == 'i'){
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
        if(actual->info == 'i'){
            avanzar();
        } else {
            fprintf(erroresSintacticos,"ERROR(%d): Se esperaba un identificador\n",ubicacion);
        }
        otroParam();
    } else if(actual->info == ')') {
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

    }else if (actual -> info == '}', actual ->info == 'o'){
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
        fprointf(erroresSintacticos,"ERROR(%d): Se esperaba 'throw'\n",ubicacion);
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