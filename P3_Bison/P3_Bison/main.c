#include <stdio.h>
#include "y.tab.h"
#include "tabla_simbolos.h"
int main(int argc, char* argv[]) {
    //inicializamos la tabla de simbolos para palabras reservadas e ID
    InicializarTablaSimbolos();
    printf("Escribe help o ?, para obtener un manual del funcionamiento de la calculadora\n");
    printf(">>>");
    yyparse();
    LiberarTabla();
    return 0;
}