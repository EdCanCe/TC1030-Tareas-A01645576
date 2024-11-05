/**
 * @file heap.h
 * @author Edmundo Canedo Cervantes - A01645576
 * @version 0.1
 * @date 2024-10-27
 */
#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#define ull unsigned long long

/**
 * @class Heap
 * 
 * @brief Tiene el arreglo del Heap, junto con los valores
 * de cada elemento y los métodos de la clase.
 * 
 * @tparam T 
 */
template <class T>
class Heap{
    private:
        T* data;
        ull sze;
        ull current;        

    public:
        std::string toString() const;
        Heap(ull);
        bool full();
        void swap(ull, ull);
        ull parent(ull);
        ull left(ull);
        ull right(ull);
        void push(T);
        bool empty();
        void pop();
        void heapify(ull);
        ull size();
        T top();
};

/**
 * @brief Convierte el Heap en un string.
 * 
 * Tiene una complejidad temporal de O(n).
 * 
 * @return std::string - El Heap como string.
 */
template <class T>
std::string Heap<T>::toString() const {
	std::stringstream aux;
	aux << "[";	
    for (unsigned int i = 0; i < current; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

/**
 * @brief Constructor del Heap.
 * 
 * @param Size El tamaño máximo que tendrá el Heap.
 */
template <class T>
Heap<T>::Heap(ull Size){
    sze=Size;
    current=0; //El tamaño actual del Heap.
    data = new T[sze];
}

/**
 * @brief Verifica si el Heap está en su capacidad
 * máxima.
 * 
 * @return TRUE - El Heap está lleno.
 * 
 * FALSE - El Heap aún tiene espacios libres.
 */
template <class T>
bool Heap<T>::full(){
    return sze==current;
}

/**
 * @brief Intercambia la posición de dos elementos
 * en el Heap.
 * 
 * @param i El índice del primer elemento a intercambiar.
 * @param j El índice del segundo elemento a intercambiar.
 */
template <class T>
void Heap<T>::swap(ull i, ull j) {
	T aux=data[i];
	data[i]=data[j];
	data[j]=aux;
}

/**
 * @brief Permite obtener el índice del padre de un elemento
 * en el Heap.
 * 
 * @param x El índice del elemento al cual se le obtendrá su
 * padre.
 * @return ull - El índice del padre.
 */
template <class T>
ull Heap<T>::parent(ull x){
    return (x)/2;
}

/**
 * @brief Permite obtener el índice del hijo izquierdo de un 
 * elemento en el Heap.
 * 
 * @param x El índice del elemento al cual se le obtendrá su
 * hijo izquierdo.
 * @return ull - El índice del hijo.
 */
template <class T>
ull Heap<T>::left(ull x){
    ull i=(x+1)*2-1;
    if(i>=current) i=x;
    return i;
}

/**
 * @brief Permite obtener el índice del hijo derecho de un 
 * elemento en el Heap.
 * 
 * @param x El índice del elemento al cual se le obtendrá su
 * hijo derecho.
 * @return ull - El índice del hijo.
 */
template <class T>
ull Heap<T>::right(ull x){
    ull i=(x+1)*2;
    if(i>=current) i=x;
    return i;
}

/**
 * @brief Añade un elemento al Heap.
 * 
 * Tiene una complejidad temporal de O(log n).
 * 
 * @param x El elemento a añadir.
 */
template <class T>
void Heap<T>::push(T x){
    if(full()) return;
    data[current]=x;
    ull aux=current, par=parent(aux);
    while(aux!=0 && data[aux]<data[par]){
        swap(aux, par);
        aux=par;
        par=parent(aux);
    }
    current++;
}

/**
 * @brief Verifica si el Heap está vacío.
 * 
 * @return TRUE - El Heap está vacío.
 * 
 * FALSE - El Heap tiene elementos.
 */
template <class T>
bool Heap<T>::empty(){
    return current==0;
}

/**
 * @brief Elimina el elemento hasta arriba
 * del Heap.
 * 
 * Tiene una complejidad temporal de O(log n).
 */
template <class T>
void Heap<T>::pop(){
    if(empty()) return;
    data[0]=0;
    swap(0,--current);
    heapify(0);
}

/**
 * @brief Acomoda los elementos del Heap en caso
 * de que algún padre sea mayor que sus hijos.
 * 
 * Tiene una complejidad temporal de O(log n).
 */
template <class T>
void Heap<T>::heapify(ull x){
    ull le=left(x), ri=right(x);
    ull mi;
    if(data[le]<data[ri]) mi=le;
    else mi=ri;
    if(data[x]>data[mi]){
        swap(x,mi);
        heapify(mi);
    }
}

/**
 * @brief Regresa el tamaño actual del Heap.
 */
template <class T>
ull Heap<T>::size(){
    return current;
}

/**
 * @brief Regresa el elemento de hasta arriba
 * del Heap.
 */
template <class T>
T Heap<T>::top(){
    if(empty()) return 0;
    return data[0];
}

#endif