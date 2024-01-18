#include "errores.h"
//Error que salta cuando cargamos un bloque donde esta la posicion de inicio de palabra

void Error_fichero(char * nombreFichero){
    printf("Error al abrir el fichero %s",nombreFichero);
}
void Error_No_Posicion_Libre(char* lexema, int n_linea){
    printf("Error con lexema en la linea %d\nNo se encuentra posicion para insertar el lexema %s libre.\n",n_linea, lexema);
}

void Error_exponente(char* lexema, int n_linea){
    printf("Error en la linea %d\nNúmero %s, tiene exponente pero no lo prosigue un numero\n",n_linea, lexema);
}
