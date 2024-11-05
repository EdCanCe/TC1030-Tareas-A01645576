/**
 * @file splay.h
 * @author Edmundo Canedo Cervantes - A01645576
 * @version 0.1
 * @date 2024-11-04
 */
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include<string>
#include<sstream>
#include<iostream>

template<class T>class SplayTree; //Se declara para usar como clase amiga

/**
 * @class Node
 * 
 * @brief La clase de un nodo, parte del splay
 * tree. 
 */
template<class T>
class Node{
    private: 
        T value;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;

        Node<T>* rot_right(Node<T>*);
        Node<T>* rot_left(Node<T>*);
        Node<T>* splay(Node<T>*, Node<T>*);
        Node<T>* succesor();

    public: 
        Node(T);
        Node(T, Node<T>*);
        Node(T, Node<T>*, Node<T>*, Node<T>*);

        Node<T>* add(T, Node<T>*);
        Node<T>* find(T);

        void inorder(std::stringstream &) const;
        void preorder(std::stringstream &) const;

    friend class SplayTree<T>;
};

/**
 * @brief Constructor del nodo.
 * 
 * Construye un nodo únicamente con su xor.
 * 
 * @param x El xor del nodo.
 */
template<class T>
Node<T>::Node(T x){
    value=x;
    parent=0;
    left=0;
    right=0;
}

/**
 * @brief Constructor del nodo.
 * 
 * Construye un nodo con su xor y padre.
 * 
 * @param x El xor del nodo.
 * @param Parent El puntero del padre.
 */
template<class T>
Node<T>::Node(T x, Node<T>* Parent){
    value=x;
    parent=Parent==nullptr ? 0 : Parent;
    left=0;
    right=0;
}

/**
 * @brief Constructor del nodo.
 * 
 * Construye un nodo con sus xores y apuntadores.
 * 
 * @param x El xor del nodo.
 * @param Parent El puntero del padre.
 * @param Left El puntero del hijo izquierdo.
 * @param Right El puntero del hijo derecho.
 */
template<class T>
Node<T>::Node(T x, Node<T>* Parent, Node<T>* Left, Node<T>* Right){
    value=x;
    parent=Parent;
    left=Left;
    right=Right;
}

/**
 * @brief Realiza una rotación a la derecha.
 * 
 * @param x El puntero del nodo a rotar.
 * @return Node<T>*- La raíz del subárbol.
 */
template<class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
    Node<T>* y=x->left; //El nodo que se terminará regresando

    if(y->right){ //El subarbol derecho de y se hace hijo de x
        x->left=y->right;
        y->right->parent=x;
    }

    y->parent=x->parent; //Se le añade el padre de x a y
    x->parent=y; //x se hace hijo de y
    y->right=x;

    if(y->parent){ //En caso de que no sea el root, y tenga un nodo como padre
        if(y->parent->left==x) y->parent->left=y;
        else y->parent->right=y;
    }

    return y;
}

/**
 * @brief Realiza una rotación a la izquierda.
 * 
 * @param x El puntero del nodo a rotar.
 * @return Node<T>*- La raíz del subárbol.
 */
template<class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
    Node<T>* y=x->right; //El nodo que se terminará regresando

    if(y->left){ //El subarbol derecho de y se hace hijo de x
        x->right=y->left;
        y->left->parent=x;
    }

    y->parent=x->parent; //Se le añade el padre de x a y
    x->parent=y; //x se hace hijo de y
    y->left=x;

    if(y->parent){ //En caso de que no sea el root, y tenga un nodo como padre
        if(y->parent->right==x) y->parent->right=y;
        else y->parent->left=y;
    }

    return y;
}

/**
 * @brief Realiza el splay para mover el último elemento insertado/buscado
 * a la raíz del árbol. Tiene una complejidad temporal de O(n).
 * 
 * @param root El puntero de la raíz del árbol.
 * @param x El puntero del elemento a mover a la raíz.
 * @return Node<T>*- La nueva raíz del árbol.
 */
template<class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
    while(x->parent!=0){ //Mientras x no sea la raíz
        if(x->parent->value==root->value){ //Si es un hijo de la raíz
            if(x->parent->left && x->parent->left->value==x->value){
                rot_right(x->parent);
            }else{
                rot_left(x->parent);
            }
        }else{ //Si NO es hijo de la raíz
            Node<T>* p=x->parent; //Obtiene su padre
            Node<T>* g=p->parent; //Obtiene su abuelo
            if(p->left && g->left && x->value==p->left->value && p->value==g->left->value){ //Dos a la derecha
                rot_right(g);
                rot_right(p);
            }else if(p->right && g->right && x->value==p->right->value && p->value==g->right->value){ //Dos a la izquierda
                rot_left(g);
                rot_left(p);
            }else if(p->left && g->right && x->value==p->left->value && p->value==g->right->value){
                rot_right(p);
                rot_left(g);
            }else{
                rot_left(p);
                rot_right(g);
            }
        }
    }
    return x;
}

/**
 * @brief Busca el nodo sucesor de otro. Tiene una
 * complejidad temporal de O(n).
 * 
 * @return Node<T>* El sucesor del nodo.
 */
template<class T>
Node<T>* Node<T>::succesor(){
    Node<T>* l=left;
    Node<T>* r=right;

    if(right->left==0){
        right=right->right;
        r->right=0;
        return r;
    }

    Node<T>* parent, * child;
    parent=right;
    child=right->left;
    while(child->left!=0){
        parent=child;
        child=child->left;
    }
    parent->left=child->right;
    child->right=0;
    return child;
}

/**
 * @brief Añade un elemento a un nodo del árbol.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param x El elemento a añadir.
 * @param previous El puntero del padre.
 * @return Node<T>* El puntero del elemento añadido.
 */
template<class T>
Node<T>* Node<T>::add(T x, Node<T>* previous){
    if(x>value){
        if(right!=0) return right->add(x, previous);
        right=new Node(x);
        return right;
    }else{
        if(left!=0) return left->add(x, previous);
        left=new Node(x);
        return left;
    }
}

/**
 * @brief Busca el nodo donde se encuentra un
 * elemento. Tiene una complejidad temporal de O(n).
 * 
 * @param x El elemento a buscar.
 * @return Node<T>* El puntero del elemento.
 */
template<class T>
Node<T>* Node<T>::find(T x){
    if(x==value) return this;
    if(x>value){
        if(right==0) return this;
        return right->find(x);
    }else{
        if(left==0) return this;
        return left->find(x);
    }
    return this;
}

/**
 * @brief Sirve para la impresión del árbol.
 * Tiene complejidad temporal de O(n).
 * 
 * @param aux El string de la salida.
 */
template<class T>
void Node<T>::inorder(std::stringstream & aux) const{
    if(left!=0){
        left->inorder(aux);
    }
    if(aux.tellp()!=1){
        aux<<" ";
    }
    aux<<value;
    if(right!=0){
        right->inorder(aux);
    }
}

/**
 * @brief Sirve para la impresión del árbol.
 * Tiene complejidad temporal de O(n).
 * 
 * @param aux El string de la salida.
 */
template<class T>
void Node<T>::preorder(std::stringstream & aux) const{
    aux<<value;
    if(left!=0){
        aux<<" ";
        left->preorder(aux);
    }
    if(right!=0){
        aux<<" ";
        right->preorder(aux);
    }
}

/**
 * @class SplayTree
 * 
 * @brief La clase del splay tree.
 */
template<class T>
class SplayTree{
    private:
        Node<T>* root;

    public: SplayTree();
        void add(T);
        bool find(T);
        void remove(T);
        bool empty();
        std::string inorder();
        std::string preorder();
};

/**
 * @brief Constructor del SpalyTree.
 * 
 */
template<class T>
SplayTree<T>::SplayTree(){
    root=0;
}

/**
 * @brief Añade un elemento al árbol.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param x El elemento a añadir.
 */
template<class T>
void SplayTree<T>::add(T x){
    if(root!=0){
        Node<T>* added=root->add(x, nullptr);
        root->splay(root, added);
    }else{
        root=new Node(x);
    }
}

/**
 * @brief Busca si se encuentra o no un elemento
 * en el árbol. Tiene una complejidad temporal de O(n).
 * 
 * @param x El elemento a buscar.
 * @return Bool Si el elemento se encuentra o no.
 */
template<class T>
bool SplayTree<T>::find(T x){
    if(root!=0){
        Node<T>* found=root->find(x);
        root->splay(root, found);
        return(root->value==x);
    }else{
        return false;
    }
}

/**
 * @brief Elimina un nodo en el árbol.
 * 
 * @param x El nodo a eliminar.
 */
template<class T>
void SplayTree<T>::remove(T x){
    if(root!=0){
        Node<T>* found=root->find(x);
        root->splay(root, found);
    }
}

/**
 * @brief Verifica si el árbol está vacío.
 * 
 * @return Bool Si el árbol está vacío. 
 */
template<class T>
bool SplayTree<T>::empty(){
    return root==0;
}

/**
 * @brief Sirve para la impresión del árbol.
 * Tiene complejidad temporal de O(n).
 * 
 * @return string El string de la impresión.
 */
template<class T>
std::string SplayTree<T>::inorder(){
    std::stringstream aux;

    aux<<"[";
    if(!empty()){
        root->inorder(aux);
    }
    aux<<"]";
    return aux.str();
}

/**
 * @brief Sirve para la impresión del árbol.
 * Tiene complejidad temporal de O(n).
 * 
 * @return string El string de la impresión.
 */
template<class T>
std::string SplayTree<T>::preorder(){
    std::stringstream aux;

    aux<<"[";
    if(!empty()){
        root->preorder(aux);
    }
    aux<<"]";
    return aux.str();
}

#endif