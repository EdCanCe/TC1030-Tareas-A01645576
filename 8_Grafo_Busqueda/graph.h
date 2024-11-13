/**
 * @file graph.h
 * @author Edmundo Canedo Cervantes - A01645576
 * @brief 
 * @version 0.1
 * @date 2024-11-13
 * 
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

/**
 * @class Graph
 * 
 * @brief Contiene los métodos y atributos para
 * tener un grafo y acceder a sus nodos.
 */
class Graph{
    private:
        vector<int> * list;
        int * mat;
        int nodes;

    public:
        void start(int);
        Graph();
        Graph(int);
        void addEdgeList(int, int);
        void addEdgeMat(int, int);
        void loadGraphList(string, int);
        void loadGraphMat(string, int, int);
        string printAdjList();
        string printAdjMat();
        string BFS(int, int);
        string DFS(int, int);
};

/**
 * @brief Inicializa el grafo con un tamaño dado.
 * 
 * @param size La cantidad de nodos.
 */
void Graph::start(int size){
    nodes=size;
    list=new vector<int>[size];
    mat=new int[size*size];
}

/**
 * @brief Constructor del grafo vacío.
 * 
 */
Graph::Graph(){
    nodes=0;
    list=0;
    mat=0;
}

/**
 * @brief Constructor del grafo con la cantidad de nodos.
 * 
 * @param size La cantidad de nodos que va a tener el grafo.
 */
Graph::Graph(int size){
    start(size);
}

/**
 * @brief Añade una conexión entre 2 nodos.
 * 
 * @param p Índice del primer nodo.
 * @param q Índice del segundo nodo.
 */
void Graph::addEdgeList(int p, int q){
    list[p].push_back(q);
    list[q].push_back(p);
}

/**
 * @brief Añade una conexión entre 2 nodos.
 * 
 * @param p Índice del primer nodo.
 * @param q Índice del segundo nodo.
 */
void Graph::addEdgeMat(int p, int q){
    mat[p*nodes+q]=1;
    mat[q*nodes+p]=1;
}

/**
 * @brief Carga las conexiones en los nodos del grafo.
 * 
 * @param conns Las conexiones.
 * @param size La cantidad de nodos.
 */
void Graph::loadGraphList(string conns, int size){
    stringstream in; in<<conns;
    char aux;

    if(nodes==0) start(size);

    while(in>>aux){ //Lee el (
        int a; in>>a; //Lee el primer índice
        in>>aux; //Lee la ,
        int b; in>>b; //Lee el segundo índice
        in>>aux; //Lee el )

        addEdgeList(a, b);
    }
}

/**
 * @brief Carga las conexiones en los nodos del grafo.
 * 
 * @param conns Las conexiones.
 * @param size La cantidad de nodos.
 * @param x La cantidad de nodos.
 */
void Graph::loadGraphMat(string conns, int size, int x){
    stringstream in; in<<conns;
    char aux;

    if(nodes==0) start(size);

    while(in>>aux){ //Lee el (
        int a; in>>a; //Lee el primer índice
        in>>aux; //Lee la ,
        int b; in>>b; //Lee el segundo índice
        in>>aux; //Lee el )

        addEdgeMat(a, b);
    }
}

/**
 * @brief Imprime la lista de conexciones.
 * 
 * @return string - La lista en string.
 */
string Graph::printAdjList(){
    stringstream aux;
    for(int i=0; i<nodes; i++){
        aux<<"vertex "<<i<<" :";
        for(int j=0; j<list[i].size(); j++){
            aux<<" "<<list[i][j];
        }
        aux<<" ";
    }
    return aux.str();

}

/**
 * @brief Imprime la matriz de conexciones.
 * 
 * @return string - La matriz en string.
 */
string Graph::printAdjMat(){
    stringstream aux;
    for(int i=0; i<nodes; i++){
        for(int j=0; j<nodes; j++){
            aux<<mat[i*nodes+j]<<" ";
        }
    }
    return aux.str();
}

string Graph::BFS(int p, int q){
    return "";
}

string Graph::DFS(int p, int q){
    return "";
}

#endif