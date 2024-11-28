/**
*
* Edmundo Canedo Cervantes
* A01645576
*
*/
#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T> class List; //Declaración de clase List para que pueda ser declarada como clase amiga en la clase "Link".

/**
 * @class Link
 * 
 * @brief Representa un nodo en la lista.
 */
template <class T>
class Link{
    private:
        T value; //El valor del nodo
        Link<T>* next; //Apunta hacia el siguiente nodo

        Link(T);
        Link(T, Link<T>&);

        friend class List<T>; //Permite que la clase "List" utilice los elementos privados de la clase "Link"
};

/**
 * @brief Constructor del nodo con valor asignado.
 * 
 * @param x El valor que el nodo va a tener.
 */
template <class T>
Link<T>::Link(T x){
    value=x;
    next=0;
};

/**
 * @brief Constructor del nodo con valor y dirección del siguiente nodo asignado.
 * 
 * @param x El valor que el nodo va a tener.
 * @param adr La dirección del siguiente nodo.
 */
template <class T>
Link<T>::Link(T x, Link<T>& adr){
    value=x;
    next=&adr;
}

/**
 * @class List
 * 
 * @brief Tiene el control de la lista y de cada uno
 * de sus nodos.
 */
template <class T>
class List{
    private:
        int size;
        Link<T>* head;

    public:
        List();
        ~List();
        
        std::string toString() const;

        void insertion(T);
        int search(T);
        void update(int, T);
        void deleteAt(int);

};

/**
 * @brief Constructor de la lista.
 */
template <class T>
List<T>::List(){
    size=0;
    head=0;
}

/**
 * @brief Destructor de la lista.
 * Tiene una complejidad temporal O(n). 
 */
template <class T>
List<T>::~List(){
    Link<T> *aux;
    while(head!=0){
        aux=head->next;
        delete head;
        head=aux;
    }
}

/**
 * @brief Convierte la lista en una cadena
 * de texto.
 * 
 * @return std::string - La lista en forma de texto.
 */
template <class T>
std::string List<T>::toString() const {
	std::stringstream aux;
	Link<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

/**
 * @brief Permite insertar un nuevo valor a la lista.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param x El valor a insertar.
 */
template <class T>
void List<T>::insertion(T x){
    if(size==0){
        head=new Link(x);
    }else{
        Link<T> *aux=head;
        while(aux->next!=0){
            aux=aux->next;
        }
        aux->next=new Link(x);
    }
    size++;
}


/**
 * @brief Permite buscar el índice de un elemento
 * en la lista. Tiene una complejidad temporal de O(n).
 * 
 * @param x El valor a buscar.
 * @return int - El índice del elemento en la lisa. Si es -1 no existe.
 */
template <class T>
int List<T>::search(T x){
    int i=0;
    Link<T> *aux=head;
    while(aux!=0){
        if(aux->value==x) return i;
        aux=aux->next;
        i++;
    }
    return -1;
}

/**
 * @brief Cambia el valor por otro en un índice dado.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param i El índice de la posición donde se cambiará el valor.
 * @param x El nuevo valor.
 */
template <class T>
void List<T>::update(int i, T x){
    if(i<0 || i>=size){
        std::__throw_out_of_range;
    }
    Link<T> *aux=head;
    while(i!=0){
        aux=aux->next;
        i--;
    }
    aux->value=x;
}

/**
 * @brief Borra el nodo en un índice dado.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param i El índice del nodo a eliminar.
 */
template <class T>
void List<T>::deleteAt(int i){
    if(i<0 || i>=size){
        std::__throw_out_of_range;
    }
    Link<T> *aux=head;
    if(i==0){
        head=head->next;
        delete aux;
        return;
    }
    i--;
    while(i!=0){
        aux=aux->next;
        i--;
    }
    Link<T> *aux2=aux->next->next;
    delete aux->next;
    aux->next=aux2;
}

#endif