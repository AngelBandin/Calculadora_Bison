
%option header-file="lex.yy.h"
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tabla_simbolos.h"
#include "y.tab.h"
tipo_simbolo lex;
char *aux;
void leer(char *linea);
void cerrar();
%}

%option yylineno
%option noyywrap

SEPARACION  ([ ]|\t|\r)+
INT [0-9]+
DECIMAL ([0-9]+\.[0-9]+([Ee][-+]?[0-9]+)?)   |   ([0-9]+[Ee][-+]?[0-9]+)   
NUMERO          {INT}|{DECIMAL}
IDENTIFICADOR [a-zA-Z_][a-zA-Z0-9_]*
STRING \"([^\"\n]|(\\.))*\"
SEMICOLON                     ;
COLON                         ,
OPERADORES                      [+*/%^,.!><()-?]|{SEMICOLON}|{COLON}
INTERROGACION [?]

%%
"exit"  {yyterminate();
        /*salir del programa*/} 
"on"    {return ON;
        /*on usado para activar echo*/}
"off"   {return OFF;
        /*off usado para desactivar echo*/}
"pi"    {yylval.num = 3.14159265358979323846; return NUM; }
"e"     { yylval.num = 2.71828182845904523536; return NUM; }

{SEPARACION}    {/*separaciones como espacios y tabulaciones que se ignoran*/}
{STRING}    {
    /*detecta string para introducir la ruta en la función load
    y se quita las comillas dobles al principio y al final de la ruta*/
    char* aux = yytext + 1;
    aux[strlen(aux)-1] = '\0';
    yylval.str = strdup(aux);
    return ARCHIVO;
}
{IDENTIFICADOR}  {
    /*detector de cadenas para palabras clave y variables
    al obtenerla buscamos en la tabla de simbolos*/
    BuscarLex(yytext, &lex,yylineno);
    yylval.str = strdup(yytext);
    free(lex.lexema);
    return lex.valor;
}

[0-9]+(\.[0-9]+([Ee][-+]?[0-9]+)?)?|[0-9]+[Ee][-+]?[0-9]+    {
    /*detector de numeros*/
    yylval.num = atof(yytext);
    return NUM;
}

\n    {
    /*detectar salto de linea*/
    return EOL;
    /*return ((int) *yytext);*/
}

"+="    {
    return MAS_IGUAL;
}

"-="    {
    return MENOS_IGUAL;
}
"*="    {
    return POR_IGUAL;
}
"/="    {
    return ENTRE_IGUAL;
}

{OPERADORES}    {
    /*Detecta los operadores*/
    return (int) yytext[0];   
}

<<EOF>> {/*Cerrar fichero abierto con load*/
        cerrar(); yyrestart(stdin);
        return ENDOFFILE;}
.    { /*devolver caracteres invalidos*/return INVALID; }
%%



void cerrar(){
    //cerrar fichero
    fclose(yyin);
}
int cargar(char* archivo){
    //cargar fichero con operaciones
    if((yyin = fopen(archivo, "r")) == NULL) {
        printf("\nFallo al abrir el archivo fuente");
        //hacer que se vuelva a analizar lo que el usuario introduce por terminal
		yyin = stdin;
        return 0;
	}
    else{
        printf("\ncargando archivo %s\n",archivo);
        return 1;
    }
}
