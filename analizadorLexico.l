%{
/* Programa que lee un programa y hace elreconocimiento de identificadores, 
palabras reservadas y enteros de un lenguaje x
*/
FILE *archSal;
%}
espacio [ ]
ident   [\$]({let}|{dig})+
caracter [']({let}|{dig}|{espacio})[']
cadena  [\"]({let}|{dig}|{espacio})+[\"]
octal   [Oo][0-7]*
decimal [1-9][0-9]*
dig     [0-9]
let     [a-zA-Z]
real    [0-9]*\.[0-9]+
entero  {dig}+
palres  alternative|big|evaluate|instead|large|loop|make|number|other|real|repeat|select|small|step|stop|symbol|throw
operrel <|>|<=|>=|==|!=
operasig :=|+=|-=|\*=|/=
operarit \+|\-|\*|\/|%|\^
operadasignacion \=
simboloespecial \[|\]|\(|\)|\{|\}|\,|\:|\;

%%
{cadena}        fprintf(archSal," %s es una cadena\n", yytext);
{caracter}      fprintf(archSal," %s es un caracter\n", yytext);
{octal} fprintf(archSal,"octal %s\n",yytext);
{decimal}       fprintf(archSal,"decimal %s\n",yytext);
{entero}  fprintf(archSal," %s es un entero\n", yytext);
{palres}  fprintf(archSal," %s es unapalabra reservada\n", yytext);
{ident}   fprintf(archSal," %s es un identificador\n", yytext);
{real}    fprintf(archSal," %s es un real\n", yytext);
{operrel}       fprintf(archSal," %s es un operador relacional\n", yytext);
{operarit}      fprintf(archSal," %s es un operador aritmetico\n", yytext);
{operadasignacion}      fprintf(archSal," %s es un operador de asignacion\n", yytext);
{simboloespecial}       fprintf(archSal," %s es un simbolo especial\n", yytext);

%%

int main(int argc, char *argv[]){
        yyin = fopen(argv[1],"r");
        archSal = fopen("lex_an_output.txt","w");
        yylex();
        fclose(archSal);
} 