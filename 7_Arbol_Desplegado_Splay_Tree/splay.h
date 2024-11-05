/**
 * @file splay.h
 * @author Edmundo Canedo Cervantes
 * @version 0.1
 * @date 2024-11-04
 */
#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <string>
#include <sstream>
#include <iostream>

template<class T> class SplayTree; //Se declara para usar como clase amiga

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
        Node(T, Node<T>*, Node<T>* ,Node<T>*);

        Node<T>* add(T);
        Node<T>* find(T);
        void remove(T);

        void inorder(std::stringstream&) const;
        void preorder(std::stringstream&) const;


    friend class SplayTree<T>;
};

/**
 * @brief Constructor del nodo.
 * 
 * Construye un nodo únicamente con su valor.
 * 
 * @param x El valor del nodo.
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
 * Construye un nodo con su valor y padre.
 * 
 * @param x El valor del nodo.
 * @param Parent El puntero del padre.
 */
template<class T>
Node<T>::Node(T x, Node<T>* Parent){
    value=x;
    parent=Parent;
    left=0;
    right=0;
}

/**
 * @brief Constructor del nodo.
 * 
 * Construye un nodo con sus valores y apuntadores.
 * 
 * @param x El valor del nodo.
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
 * @return Node<T>* - La raíz del subárbol.
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
 * @return Node<T>* - La raíz del subárbol.
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
 * @return Node<T>* - La nueva raíz del árbol.
 */
template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
    while(x->parent!=0){
        if(x->parent->value==root->value){
            if(x->parent->left && x->parent->left->value==x->value){
                rot_right(x->parent);
            }else{
                rot_left(x->parent);
            }
        }else{
            Node<T>*p=x->parent;
            Node<T>*g=p->parent;
            if(p->left && g->left && x->value==p->left->value && p->value==g->left->value){
                rot_right(g);
                rot_right(p);
            }else if(p->right && g->right && x->value==p->right->value && p->value==g->right->value){
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

template<class T>
Node<T>* Node<T>::succesor(){
    return 0;
}

template <class T>
Node<T>* Node<T>::add(T x){
    if(x > value){
        if(right!=0) return right->add(x);
        right=new Node(x);
        return right;
    }else{
        if(left!=0) return left->add(x);
        left=new Node(x);
        return left;
    }
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        right->inorder(aux);
    }
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template<class T>
class SplayTree{
    private:
        Node<T>* root;

    public:
        SplayTree();
        void add(T);
        Node<T>* find(T);
        void remove(T);
        bool empty();
        std::string inorder();
        std::string preorder();
};

template <class T>
SplayTree<T>::SplayTree(){
    root=0;
}

template<class T>
void SplayTree<T>::add(T x){
    if(root!=0){
        Node<T>* added=root->add(x);
        root->splay(root, added);
    }else{
        root=new Node(x);
    }
}

template<class T>
Node<T>* SplayTree<T>::find(T x){
    return root->find(x);
}

template<class T>
void SplayTree<T>::remove(T x){
}

template<class T>
bool SplayTree<T>::empty(){
    return root==0;
}

template<class T>
std::string SplayTree<T>::inorder() {
    std::stringstream aux;

    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template<class T>
std::string SplayTree<T>::preorder() {
    std::stringstream aux;

    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif