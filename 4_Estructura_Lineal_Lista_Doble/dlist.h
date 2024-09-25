/**
 * @file dlist.h
 * @author Edmundo Canedo Cervantes - A01645576
 * @version 0.1
 * @date 2024-09-24
 */
#ifndef DLIST_H
#define DLIST_H
#define Node Link<T>*

#include<iostream>

template <class T> class DList; //Se declara para poder usar como clase amiga.

/**
 * @class Link
 * 
 * @brief Son los nodos, contienen su valor, y el 
 * puntero hacia un nodo pasado y siguiente.
 */
template <class T>
class Link{
    private:
        T value;
        Node next;
        Node prev;

        Link(T);
        Link(T, Node, Node);

        friend class DList<T>; //Se declara como variable amiga para que pueda usar sus atributos.
};

/**
 * @brief Constructor del nodo.
 * 
 * Únicame inicializa su valor.
 * 
 * Los punteros hacia los otros 
 * nodos los inicia en 0.
 * 
 * @param x El valor que el nodo tendrá.
 */
template <class T>
Link<T>::Link(T x){
    value=x;
    next=0;
    prev=0;
}

/**
 * @brief Constructor del nodo.
 * 
 * Le asigna al nodo el valor que tomará
 * junto con los punteros que tiene.
 * 
 * @param x El valor que el nodo tendrá.
 * @param Prev Puntero hacia el anterior nodo.
 * @param Next Puntero hacia el siguiente nodo.
 */
template <class T>
Link<T>::Link(T x, Node Prev, Node Next){
    value=x;
    next=Next;
    prev=Prev;
}

/**
 * @class DList
 * 
 * @brief Guarda la lista, junto con la cabeza
 * y la cola de la estructura de datos y las
 * funciones que tiene para acceder, borrar
 * modificar y agregar datos. 
 */
template <class T>
class DList{
    private:
        int size; //El tamaño de la lista
        Node head; //Puntero hacia la cabeza
        Node tail; //Puntero hacia la cola
        bool empty();
        void drop(Node);

    public:
        DList();
        std::string toStringForward()const;
        std::string toStringBackward()const;
        void insertion(T);
        int search(T);
        void update(int, T);
        void deleteAt(int);
};

/**
 * @brief Constructor de la lista.
 */
template <class T>
DList<T>::DList() {
	size=0;
	head=0;
	tail=0;
}

/**
 * @brief Convierte la lista en una cadena de texto.
 * 
 * La convierte de la cabeza hacia la cola.
 * 
 * @return std::string - La lista como cadena.
 */
template <class T>
std::string DList<T>::toStringForward() const {
    if(size==0) return "[]";
    std::stringstream s;
    Node aux=head;
    s<<"[";
    while(aux->next!=0){
        s<<aux->value<<", ";
        aux=aux->next;
    }
    s<<aux->value<<"]";
    return s.str();
}

/**
 * @brief Convierte la lista en una cadena de texto.
 * 
 * La convierte de la cola hacia la cabeza.
 * 
 * @return std::string - La lista como cadena.
 */
template <class T>
std::string DList<T>::toStringBackward() const {
    if(size==0) return "[]";
    std::stringstream s;
    Node aux=tail;
    s<<"[";
    while(aux->prev!=0){
        s<<aux->value<<", ";
        aux=aux->prev;
    }
    s<<aux->value<<"]";
    return s.str();
}

/**
 * @brief Permite inertar nuevos nodos
 * a la lista.
 * 
 * Tiene una complejidad temporal de O(1).
 * 
 * @param x El valor a insertar.
 */
template <class T>
void DList<T>::insertion(T x){
    if(empty()){
        Node aux=new Link(x);
        head=aux;
        tail=aux;
    }else{
        Node aux= new Link(x);
        aux->prev=tail;
        tail->next=aux;
        tail=aux;
    }
    size++;
}

/**
 * @brief Permite entontrar el índice de un elemento
 * en la lista.
 * 
 * Tiene una complejidad temporal de O(n).
 * 
 * @param x El valor a buscar.
 * @return int - El índice del elemento (si es -1 no existe).
 */
template <class T>
int DList<T>::search(T x){
    if(empty()) std::__throw_out_of_range;
    Node aux=head;
    int i=0;
    while(aux!=0){
        if(aux->value==x) return i;
        aux=aux->next;
        i++;
    }
    return -1;
}

/**
 * @brief Permite modificar el valor de un elemento
 * en un índice.
 * 
 * Tiene una complejidad temporal de O(n).
 * 
 * @param j El índice del elemento a modificar.
 * @param x El nuevo valor que tendrá.
 */
template <class T>
void DList<T>::update(int j, T x){
    if(j<0 || j>=size) std::__throw_out_of_range;
    if(j<(size/2)){
        Node aux=head;
        int i=0;
        while(aux!=0 && i<j){
            if(aux->value==x) break;
            aux=aux->next;
            i++;
        }
        aux->value=x;
    }else{
        Node aux=tail;
        int i=size-1;
        while(aux!=0 && i>j){
            if(aux->value==x) break;
            aux=aux->prev;
            i--;
        }
        aux->value=x;
    }
}

/**
 * @brief Permite eliminar un elemento en la lista.
 * 
 * Tiene una complejidad temporal de O(n).
 * 
 * @param j El índice del elemento a modificar.
 */
template <class T>
void DList<T>::deleteAt(int j){
    if(j<0 || j>=size) std::__throw_out_of_range;
    if(j<(size/2)){
        Node aux=head;
        int i=0;
        while(aux!=0 && i<j){
            aux=aux->next;
            i++;
        }
        drop(aux);
    }else{
        Node aux=tail;
        int i=size-1;
        while(aux!=0 && i>j){
            aux=aux->prev;
            i--;
        }
        drop(aux);
    }
    size--;
}

/**
 * @brief Te dice si la lista está vacía.
 * 
 * @return TRUE - La lista está vacía
 * 
 * FALSE - La lista tiene algún elemento.
 */
template <class T>
bool DList<T>::empty(){
    return size==0;
}

/**
 * @brief Elimina un nodo de la lista, juntando
 * los 2 nodos que tiene al lado.
 * 
 * @param one - El nodo a eliminar
 */
template <class T>
void DList<T>::drop(Node one){
    if(one->prev!=0) one->prev->next=one->next;
    else head=one->next;
    if(one->next!=0) one->next->prev=one->prev;
    else tail=one->prev;
}

#endif