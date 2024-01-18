#include "tabla_hash_recolocacion.h"

/* TABLA HASH CON RECOLOCACION */

//Al inicializar igualo el tamaño maximo al tamaño máximo inicial de la tabla, inicializo el 
//tamaño ocupado actual a 0 y reservo memoria a la tabla
//despues inicio todos los valores a -1 y cadenas a null
void InicializarTablaHash(TablaHash* t) {
    int i;
    t->Tam_max = Tam;
    t->Tam_ocupado = 0;
    t->tabla = (tipo_simbolo *) malloc(sizeof(tipo_simbolo) * Tam);
    for (i = 0; i < Tam; i++){
        t->tabla[i].valor = -1;
        t->tabla[i].lexema =NULL;
        t->tabla[i].init = 0;
    }
}


/******* FUNCION HASH *******/

//función Hash que usare para buscar e insertar los elementos en la tabla
  int Hash (char *cad, int tamano){
     int i,suma=0;
     for (i=strlen(cad)-1;i>=0;i--){
         suma=(suma*256+cad[i])%tamano;
     }
     return suma;
 }

//Obtengo la posicion en la tabla dada la función hash y verificamos que en esa posicion
//este la cadena que buscamos, sino se da una iteración en el bucle y se suma el valor de a* i
//hasta que encontremos la posición donde esta la cadena.
//si encuentra null sin embargo, quiere decir que la cadena no esta en la tabla 
int _PosicionBuscar(TablaHash t, char *cad) {

    int ini, i, aux, a;
    ini = Hash(cad, t.Tam_max);
    a=9;
    for (i = 0; i < Tam; i++) {
        aux = (ini + a*i) % Tam;
        if (t.tabla[aux].lexema == NULL)
            return aux;
        else if(cad== NULL);
        else if(!strcmp(t.tabla[aux].lexema, cad))
            return aux;
    }
    return ini;
}

//Funcion que localiza la posicion para insertar un elemento
//utiliza el mismo metodo que para buscar posicion, pero sigue buscando si el espacio
//esta ocupado e inserta cuando encuentra que el lexema en la posición es == NULL
int _PosicionInsertar(TablaHash t, char *cad) {
    // Devuelve el sitio donde podriamos poner el elemento de clave cad

    int ini, aux, i, a;
    a=9;
    ini = Hash(cad,t.Tam_max);
  
    for (i = 0; i < Tam; i++) {
        aux = (ini + a*i) % Tam;
        if (t.tabla[aux].lexema == NULL){
            return aux;
        }
        if (!strcmp(t.tabla[aux].lexema, cad)){
            return aux;
        }
    }
    return ini;
}
// Busca la posición dada la cadena introducida y en esa posicion recupera el valor y el lexema
//para la cadena del lexema primero se hace un malloc de e->lexema, del tipo_simbolo que
//introducimos como argumento con el tamaño de la cadena en tabla +1 por el \0 y copiamos el 
//valor de la tabla con strcpy
//retorna 1 si encuentra el lexema, devuelve 0 en caso contrario
int Busqueda(TablaHash t, char *clavebuscar, tipo_simbolo *e) {
    
    int pos = _PosicionBuscar(t,clavebuscar);

    if ( !(t.tabla[pos].lexema == NULL) && strcmp(t.tabla[pos].lexema, clavebuscar) == 0){
         e->valor = t.tabla[pos].valor;
        e->lexema = (char*)malloc((strlen(t.tabla[pos].lexema)+1)* sizeof(char));
        if(e->valor==ID && (e->init = t.tabla[pos].init)){
            e->numero = t.tabla[pos].numero;
        }
        strcpy(e->lexema,t.tabla[pos].lexema);
        return 1;
    }
    return 0;
}

/* Función que inserta un elemento en la tabla */
void InsertarHash(TablaHash *t, char* cad, int v, int n_linea) {
    int pos, i;
    TablaHash aux;
    //obtenemos la posicion en la que insertar
    pos = _PosicionInsertar(*t,cad);
    if (t->tabla[pos].lexema == NULL) {
        //si no es null, introducimos el valor, reservamos memoria para la cadena y hacemos
        //un strcpy
        t->tabla[pos].valor=v;
        t->tabla[pos].lexema=strdup(cad);
        strcpy(t->tabla[pos].lexema, cad);//importante
        t->Tam_ocupado++; //aumentamos el tamaño ocupado
        //para que  la tabla hash funcione bien sin tener altos costes de recolocación
        // o que incluso en algunos casos no llegue a entontrar los elementos, duplicaremos el
        //tamaño cuando el tamaño ocupado llegue a ser un 75% del máximo, este es un limite aceptable
        //en base a la wikipedia y busquedas en chatgpt
        if(t->Tam_ocupado*1.5>=t->Tam_max){
            //doblo el tamaño maximo y creo una tabla auxiliar donde guardar la nueva tabla
            //con el nuevo tamaño, auxiliar donde voy a insertar los elementos de la tabla 
            //antes del cambio de tamaño
            t->Tam_max += t->Tam_max;

            aux.Tam_max = t->Tam_max;
            aux.Tam_ocupado = 0;
            aux.tabla = (tipo_simbolo *) malloc(sizeof(tipo_simbolo) * aux.Tam_max);
            for (i = 0; i < aux.Tam_max; i++){
                aux.tabla[i].valor = -1;
                aux.tabla[i].lexema =NULL;
            }
            for (i = 0; i < (t->Tam_max / 2); i++){
                if(t->tabla[i].valor == -1)aux.tabla[i].valor= -1;
                else{
                    InsertarHash(&aux,t->tabla[i].lexema,t->tabla[i].valor, n_linea);
                }
            }
            //Hago free de la memoria de la tabla de antes del cambio de tamaño
            for (i = 0; i < (t->Tam_max/2); i++){
                free(t->tabla[i].lexema);
            }
            free(t->tabla);
            //hago que la tabla ahora null, apunte a la nueva tabla con el tamaño duplicado
            t->tabla = aux.tabla;
        }
    } 
    else if (strcmp(t->tabla[pos].lexema,cad)){
        Error_No_Posicion_Libre(cad, n_linea);
    }
}
void ModificarVariable(TablaHash *t, char* cad, double numero){
    int pos = _PosicionBuscar(*t,cad);

    if (t->tabla[pos].lexema != NULL){

        if (strcmp(t->tabla[pos].lexema, cad) == 0) {
            if(t->tabla[pos].valor==ID){
                t->tabla[pos].init = 1;
                t->tabla[pos].numero = numero;
            }
        }
    }
}
void InsertarVariable(TablaHash *t, char* cad, int v,double numero, int n_linea){
    int pos, i;
    TablaHash aux;
    //obtenemos la posicion en la que insertar
    pos = _PosicionInsertar(*t,cad);
    if (t->tabla[pos].lexema == NULL) {
        //si no es null, introducimos el valor, reservamos memoria para la cadena y hacemos
        //un strcpy
        t->tabla[pos].valor=v;
        t->tabla[pos].lexema=malloc((strlen(cad)+1)*sizeof(char));
        t->tabla[pos].numero=numero;
        strcpy(t->tabla[pos].lexema, cad);//importante
        t->Tam_ocupado++; //aumentamos el tamaño ocupado
        //para que  la tabla hash funcione bien sin tener altos costes de recolocación
        // o que incluso en algunos casos no llegue a entontrar los elementos, duplicaremos el
        //tamaño cuando el tamaño ocupado llegue a ser un 75% del máximo, este es un limite aceptable
        //en base a la wikipedia y busquedas en chatgpt
        if(t->Tam_ocupado*1.5>=t->Tam_max){
            //doblo el tamaño maximo y creo una tabla auxiliar donde guardar la nueva tabla
            //con el nuevo tamaño, auxiliar donde voy a insertar los elementos de la tabla 
            //antes del cambio de tamaño
            t->Tam_max += t->Tam_max;

            aux.Tam_max = t->Tam_max;
            aux.Tam_ocupado = 0;
            aux.tabla = (tipo_simbolo *) malloc(sizeof(tipo_simbolo) * aux.Tam_max);
            for (i = 0; i < aux.Tam_max; i++){
                aux.tabla[i].valor = -1;
                aux.tabla[i].lexema =NULL;
                t->tabla[i].init = 0;
            }
            for (i = 0; i < (t->Tam_max / 2); i++){
                if(t->tabla[i].valor == -1)aux.tabla[i].valor= -1;
                else{
                    InsertarVariable(&aux,t->tabla[i].lexema,t->tabla[i].valor,numero, n_linea);
                    aux.tabla[i].init= t->tabla[i].init;
                }
            }
            //Hago free de la memoria de la tabla de antes del cambio de tamaño
            for (i = 0; i < (t->Tam_max/2); i++){
                free(t->tabla[i].lexema);
            }
            free(t->tabla);
            //hago que la tabla ahora null, apunte a la nueva tabla con el tamaño duplicado
            t->tabla = aux.tabla;
        }
    } 
    else if (strcmp(t->tabla[pos].lexema,cad)){
        Error_No_Posicion_Libre(cad, n_linea);
    }
}
//hacemos free te todas las cadenas de todas las posiciones de la tabla de simbolos y luego
//hacemos free de la propia tabla para liberar la tabla hash
int LiberarHash(TablaHash* t) {
    int i;
    for (i = 0; i < (t->Tam_max); i++){
        free(t->tabla[i].lexema);
        t->tabla[i].init=0;
        t->tabla[i].valor=-1;
    }
    free(t->tabla);
    return 1;
}
//función que libera las variables declaradas
//liberamos las cadenas de las variables, cambiamos el valor a -1 para que reconozca como vacia
//y poner init a 0 para que al declarar variable no la detecte como inicializada
void Freeworkspace(TablaHash* t){
    int i;
    for (i = 0; i < (t->Tam_max); i++){
        if(t->tabla[i].valor == ID){
            free(t->tabla[i].lexema);
            t->tabla[i].init=0;
            t->tabla[i].valor=-1;
        }
        
    }
}
//función que imprime las variables declaradas
//imprime la variable y su valor si esta inicializado
void Printworkspace(TablaHash t){
    int i;
    for (i = 0; i < (t.Tam_max); i++){
        if(t.tabla[i].valor == ID){
            if(t.tabla[i].init==1)printf("\nVariable: %s\tValor: %f\n",t.tabla[i].lexema, t.tabla[i].numero);
            else printf("\nVariable: %s\tValor: No asignado\n",t.tabla[i].lexema);
        }
    }
}
