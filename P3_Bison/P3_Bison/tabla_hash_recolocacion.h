/* 
 * File:   tablas_hash_recolocacion.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errores.h"
#include "y.tab.h"

#define Tam 1000 //tamaño maximo inicial de la tabla


//estructura de tipo simbolo que tiene el valor y cadena de los lexemas
typedef struct{
    char *lexema;
    int valor;
    double numero;
    int init;
}tipo_simbolo;


//estructura de la tabla, con un puntero tipo_simbolo donde se guardaran los datos
//Tam_max es el tamaño de la tabla, y tam_Ocupado hasta el momento, que cuando llegue a cierto 
//ratio respecto a Tam_max, se ampliara la tabla
typedef struct{
    tipo_simbolo *tabla;
    size_t Tam_max;
    size_t Tam_ocupado;
}TablaHash;

//ixicializa la tabla hash
void InicializarTablaHash(TablaHash* t);
//Busqueda con la cadena en la tabla hash y devolución del tipo_simbolo encontrado
int Busqueda(TablaHash t, char *cad, tipo_simbolo *e);

void ModificarVariable(TablaHash *t, char* cad, double numero);
//insertar cadena y valor en la tabla de simbolos
void InsertarHash(TablaHash *t, char* cad, int v, int n_linea);
void InsertarVariable(TablaHash *t, char* cad, int v,double numero, int n_linea);
//funcion para liberar tabla hash
int LiberarHash(TablaHash* t);
void Freeworkspace(TablaHash* t);
void Printworkspace(TablaHash t);