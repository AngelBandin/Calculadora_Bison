#include <stdio.h>
#include "tabla_hash_recolocacion.h"
#include "y.tab.h"


//función para inicializar la tabla de simbolos con palabras reservadas
void InicializarTablaSimbolos();
//funcion para buscar lexema
void ModificarID(char* cad, double numero);
int BuscarLex(char* cad, tipo_simbolo *e, int n_linea);
//funcion para liberar la tabla de símbolos
void LiberarTabla();
//función que libera las variables declaradas
void Liberar_workspace();
//función que imprime las variables declaradas
void Imprimir_workspace();