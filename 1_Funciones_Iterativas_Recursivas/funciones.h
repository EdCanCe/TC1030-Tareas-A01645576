/**
*
* Edmundo Canedo Cervantes
* A01645576
*
*/
#ifndef FUNCIONES_H_
#define FUNCIONES_H_

class Funciones{
    public:
    int sumaIterativa(int);
    int sumaRecursiva(int);
    int sumaDirecta(int);
};

/**
* @brief Permite realizar la suma de todos los números
* antes, y contando también a un número n por
* medio de un ciclo.
*
* Complejidad: O(n).
*
* @param int n: El número a sumar.
* @return La suma de los números.
*/
int Funciones::sumaIterativa(int n){
    int c=0;
    for(int i=0; i<=n; i++) c+=i;
    return c;
} 

/**
* @brief Permite realizar la suma de todos los números
* antes, y contando también a un número n por
* medio de una función recursiva.
*
* Complejidad: O(n).
*
* @param int n: El número a sumar.
* @return La suma de los números.
*/
int Funciones::sumaRecursiva(int n){
    if(n==0) return 0;
    return n+sumaRecursiva(n-1);
} 

/**
* @brief Permite realizar la suma de todos los números
* antes, y contando también a un número n por
* medio de una fórmula.
*
* Complejidad: O(1).
*
* @param int n: El número a sumar.
* @return La suma de los números.
*/
int Funciones::sumaDirecta(int n){
    return n*(n+1)/2;
} 

#endif