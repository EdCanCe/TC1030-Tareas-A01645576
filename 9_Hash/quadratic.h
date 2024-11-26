/**
 * @file quadratic.h
 * @author Edmundo Canedo Cervantes - A01645576
 * @date 2024-11-25
 */
#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <iostream>
#include<string>
#include<sstream>
using namespace std;

/**
 * @class Quadratics
 * 
 * Contiene métodos y atributos para implementar un
 * mapa(hash).
 */
template<class Key, class Value>
class Quadratic{
    private:
        unsigned int size;
        unsigned int current;
        unsigned int(*f)(const Key);
        Key initialValue;

        Key* keys;
        Value* values;

    public:
        Quadratic(unsigned int, Key, unsigned int(*f)(const Key));
        bool full();
        long getIndex(Key); 
        void put(Key, Value);
        Value get(Key);
        string toString();
};

/**
 * @brief Constructor del mapa.

 * @param Size Cantidad de elementos.
 * @param InitialValue Valor por defecto de la llave.
 * @param F Función de hash.
 */
template<class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int Size, Key InitialValue, unsigned int(*F)(const Key)){
    size=Size;
    current=0;
    f=F;
    initialValue=InitialValue;
    keys=new Key[size];
    values=new Value[size];
    for(long i=0; i<size; i++){ //Inicializa las llaves y valores
        keys[i]=initialValue;
        values[i]=0;
    }
}

/**
 * @brief Checa si el mapa está lleno.
 * 
 * @return TRUE si el mapa está lleno | FALSO si el mapa
 * tiene espacios vacíos. 
 */
template<class Key, class Value>
bool Quadratic<Key, Value>::full(){
    return current==size;
}

/**
 * @brief Obtiene el índice de un elemento
 * dependiendo de una llave. Tiene una complejidad
 * temporal de O(n).
 * 
 * Se da por sentado que el elemento SI existe en 
 * el mapa.
 * 
 * @param id La llave a buscar.
 * @return long - El índice del elemento.
 */
template<class Key, class Value>
long Quadratic<Key, Value>::getIndex(Key id){
    long start=f(id)%size;
	long i=start, x=1;
	if(keys[i]==id) return i;

	while(keys[i]!=id){ //Itera, en caso de regresar a donde se empezó regresa -1 porque no existe el elemento
		i=start+x*x;
        x++;
		i%=size;
	}

	return i;
}

/**
 * @brief Le añade un valor a un mapa vinculado
 * a una llave. Tiene una complejidad temporal
 * de O(n).
 * 
 * @param id La llave del valor.
 * @param val El valor.
 */
template<class Key, class Value>
void Quadratic<Key, Value>::put(Key id, Value val){
    if(full()) return;

	long start=f(id)%size;
	long i=start, x=1;

	while(keys[i]!=initialValue){ //Mientras la llave sea distinta al valor inicial, es decir, busca un índice vacío
		i=start+x*x;
        x++;
		i%=size;
	}

	keys[i]=id;
	values[i]=val;
	current++;
}

/**
 * @brief Obtiene el valor de un elemento dependiendo
 * de su llave. Tiene una complejidad temporal de O(n).
 * 
 * @param id La llave del elemento.
 * @return Value - El valor del elemento.
 */
template<class Key, class Value>
Value Quadratic<Key, Value>::get(Key id){
    long pos=getIndex(id);
    return values[pos];
}

/**
 * @brief Imprime el mapa. Tiene una complejidad
 * temporal de O(n).
 */
template<class Key, class Value>
string Quadratic<Key, Value>::toString(){
    stringstream s;
    for(long i=0; i<size; i++){
        if(keys[i]!=initialValue) s<<"("<<i<<" "<<keys[i]<<" : "<<values[i]<<") ";
    }
    return s.str();
}

#endif