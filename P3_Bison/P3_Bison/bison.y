%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "lex.yy.h"
#include "tabla_simbolos.h"
int error = 0;
int echo = 1;
int arch = 0;
tipo_simbolo aux;
extern int yylex();
extern void yyerror(const char *s);
extern double numero_ID(char* str);
extern void verAyuda();
extern double numero_ID(char* str);
extern int cargar(char* archivo);
%}


%union {
    double  num;
    char    *str ;
}
%start input
%token <num> NUM
%token <str> ID
%token <str> ARCHIVO

%token SENO COSENO TANGENTE ARCSENO ARCCOSENO ARCTANG
%token LOG LOGNEP EXP SQRT MAS_IGUAL MENOS_IGUAL POR_IGUAL ENTRE_IGUAL
%token LOAD HELP CLEAR WORKSPACE ECHO ON OFF INVALID
%token EOL ENDOFFILE

%right '=' 
%left '-' '+' MAS_IGUAL MENOS_IGUAL
%left '*' '/' '%' POR_IGUAL ENTRE_IGUAL
%left '>' '<'
%left UMINUS
%right '^'

%type <num> expr
%type <num> comp
%type <num> oper
%type <num> asign

%%
input:
    |input program  {if(!arch)printf("\n>>>");}
    |error {yyerror("\nComando invalido, usa help, para ver los comandos y operaciones disponibles");
            yyrestart(stdin);
            printf("\n>>>");}
;
program:
    expr EOL          { /*expresiones que no acaban en ;*/
                        if(error)error=0;
                        else if(echo)printf("%.6g\n", $1); 
                    }
    |expr ENDOFFILE { /*expresiones que no acaban en ; en ultima linea de fichero con operaciones*/
                        if(arch){
                            if(error)error=0;
                            else if(echo)printf("%.6g\n", $1);
                            arch = 0;
                        }
                        else{
                            yyerror("\nComando invalido, usa help, para ver los comandos y operaciones disponibles");
                        }
                    }
    | expr';' EOL {/*expresiones que acaban en ;, no se hace echo de resultado*/
                    if(error)error=0;}

    | expr';' ENDOFFILE {
                    /*expresiones que acaban en ;, en ultima linea de fichero de operaciones*/
                    if(arch){
                        if(error)error=0;
                        arch = 0;
                    }
                    else{
                            yyerror("\nComando invalido, usa help, para ver los comandos y operaciones disponibles");
                        }
                    }
    | EOL          {if(error)error=0;}
    | ENDOFFILE {arch = 0; if(error)error=0;}
    | funct EOL {if(error)error=0;}
    | funct ENDOFFILE {
                    if(arch){
                        if(error)error=0;
                        arch = 0;
                    }
                    else{
                            yyerror("\nComando invalido, usa help, para ver los comandos y operaciones disponibles");
                        }
                    }
    ;
funct:
     HELP  {/*funcion de abrir ayuda*/
            verAyuda();}
    | '?'  {/*funcion de abrir ayuda*/
            verAyuda();}
    | CLEAR {/*funcion para liberar workspace*/
            Liberar_workspace();}
    | WORKSPACE {/*funcion para imprimir workspace*/
                Imprimir_workspace();}
    | ECHO ON   {/*Activar echo de funciones*/
                echo=1;}
    | ECHO OFF  {/*Desactivar echo de funciones*/
                echo=0;}
    ;
expr:
    NUM                 {$$ = $1;}
    |ID {$$ = numero_ID($1);}
    |asign
    |comp
    | '('expr')'  {$$ = $2;}
    | oper
    | LOAD'('ARCHIVO')'{
        error = 1;
        arch = cargar($3);
        }
    ;
asign:
    ID '=' expr            {ModificarID($1, $3);
                            $$ = $3;}
    |ID MAS_IGUAL expr     {$$ = numero_ID($1) + $3;
                                ModificarID($1, $$);}
    |ID MENOS_IGUAL expr      {$$ = numero_ID($1) - $3;
                                ModificarID($1, $$);}
    |ID POR_IGUAL expr     {$$ = numero_ID($1) * $3;
                                ModificarID($1, $$);}
    |ID ENTRE_IGUAL expr      {$$ = numero_ID($1) / $3;
                                ModificarID($1, $$);}
    |NUM '=' expr            {/*Errores de asignacion de constantes*/
                                yyerror("No puedes asignar valor a constante");error=1;}
    |NUM  MAS_IGUAL expr     {yyerror("No puedes asignar valor a constante");error=1;}
    |NUM  MENOS_IGUAL expr      {yyerror("No puedes asignar valor a constante");error=1;}
    |NUM  POR_IGUAL expr     {yyerror("No puedes asignar valor a constante");error=1;}
    |NUM  ENTRE_IGUAL expr      {yyerror("No puedes asignar valor a constante");error=1;}
    ;
comp:
    expr '>' expr       {if($1 > $3) printf("Verdadero\n");
                        else printf("Falso\n");}
    |expr '<' expr       {if($1 < $3) printf("Verdadero\n");
                        else printf("Falso\n");}
    ;

oper:
    expr '+' expr   {$$ = $1 + $3;}
    | expr '-' expr     {$$ = $1 - $3;}
    | expr '*' expr     {$$ = $1 * $3;}
    | expr '/' expr       { $$ = $1 / $3; }
    | expr '%' expr       { $$ = fmod($1, $3); } 
    | expr '^' expr        { $$ = pow($1, $3); } 
    | '-' expr %prec UMINUS { $$ = -$2; }
    | SENO '('expr')'          { $$ = sin($3); }
    | COSENO '('expr')'           { $$ = cos($3); }
    | TANGENTE '('expr')'           { $$ = tan($3); }
    | ARCSENO '('expr')'          { $$ = asin($3); }
    | ARCCOSENO '('expr')'          { $$ = acos($3); }
    | ARCTANG '('expr')'         { $$ = atan($3); }
    | LOG '('expr')'          { $$ = log10($3); }
    | LOGNEP '('expr')'          { $$ = log($3); }
    | EXP '('expr')'           { $$ = exp($3); }
    | SQRT '('expr')'         { $$ = sqrt($3); }
;

    

%%

void yyerror(const char *s) {
    /*funcion para lanzar erroes*/
    printf("Error: %s\n", s);
}

void verAyuda(){
    /*funcion para mostrar contenido de fichero de ayuda*/
	FILE *ayuda;
	if((ayuda = fopen("HELP.txt", "r")) == NULL){
        yyerror("Parece que la ayuda se ha perdido. Buena suerte!");
        error = 1;
    }
	else{
		fclose(ayuda);
		system("cat HELP.txt");
	}
}
double numero_ID(char* str){
    /*Función para obtener el valor de una variable de la tabla de simbolos*/
    BuscarLex(str,&aux,0);
    free(aux.lexema);
    if(aux.init == 0){ //si no esta inicalizada se salta un error
        yyerror("Variable no inicializada");
        error = 1;
        return 0;
    }
    else return aux.numero;
}

