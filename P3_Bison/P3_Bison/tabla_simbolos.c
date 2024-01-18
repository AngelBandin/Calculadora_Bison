//

//

#include "tabla_simbolos.h"

TablaHash T;
//Inicializo tabla de simbolos con  los valores reservados
//funcion para insertar un nuevo lexema a la tabla
void InsertarID(char* cad, int v, int n_linea){
    InsertarHash(&T, cad, v, n_linea);
}
//inicializamos la tabla hash y luego insertamos las palabras reservadas del lenguaje D
void InicializarTablaSimbolos(){
    InicializarTablaHash(&T);
    InsertarID("log",LOG,0);
    InsertarID("ln",LOGNEP,0);
    InsertarID("sin",SENO,0);
    InsertarID("cos",COSENO,0);
    InsertarID("tan",TANGENTE,0);
    InsertarID("arcsin",ARCSENO,0);
    InsertarID("arccos",ARCCOSENO,0);
    InsertarID("arctan",ARCTANG,0);
    InsertarID("sqrt",SQRT,0);
    InsertarID("exp",EXP,0);
    InsertarID("load",LOAD,0);
    InsertarID("help",HELP,0);
    InsertarID("clear",CLEAR,0);
    InsertarID("workspace",WORKSPACE,0);
    InsertarID("echo",ECHO,0);
}

void ModificarID(char* cad, double numero){
    ModificarVariable(&T,cad,numero);
}
//funcion que devuelve valor, si no esta en tabla, quiere decir que es un identificador
//entonces lo insertamos en la tabla
int BuscarLex(char* cad, tipo_simbolo *e, int n_linea){
    //si la busqueda devuelve 1 quiere decir que estaba en la tabla y que se le ha dado
    //valor a e
    int o=Busqueda(T, cad, e);
    if(o==1)return 1;

    //si o esta en la tabla, la insertando con el valor ID
    else{
        InsertarID(cad,ID,n_linea);
        e->valor=ID;

        //y reservamos memoria para la cadena del lexema y le damos el valor de la cadena
        //entrada de BuscarLex
        e->lexema=malloc((strlen(cad)+1)*sizeof(char));
        strcpy(e->lexema, cad);
        return 1;
    }
}
//funcion que libera la tabla de simbolos
void LiberarTabla(){
    LiberarHash(&T);
}
//función que libera las variables declaradas
void Liberar_workspace(){
    Freeworkspace(&T);
}
//función que imprime las variables declaradas
void Imprimir_workspace(){
    Printworkspace(T);
}
