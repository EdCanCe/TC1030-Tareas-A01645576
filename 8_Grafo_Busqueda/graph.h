/**
 * @file graph.h
 * @author Edmundo Canedo Cervantes - A01645576
 * @date 2024-11-13
 * 
 */
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
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
        string print_visited(vector<int>);
        string print_path(vector<vector<int>>&, int, int);
        bool contains(vector<int>, int);
        string breadthHelper(int, int, queue<int>&, vector<int>&, vector<vector<int>>&);
        string depthHelper(int, int, stack<int>&, vector<int>&, vector<vector<int>>&);
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
    for(int i=0; i<nodes; i++){
        for(int j=0; j<nodes; j++){
            mat[i*nodes+j]=0;
        }
    }
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
        sort(list[i].begin(), list[i].end());
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

/**
 * @brief Verifica si el nodo se encuentra en el vector
 * de visitados. Tiene una complejidad temporal de O(n).
 * 
 * @param v El vector de visitados.
 * @param node El nodo a verificar.
 * @return TRUE - El nodo ya se visitó.
 * 
 * FALSE - El nodo aún no se ha visitado.
 */
bool Graph::contains(vector<int> v, int node){
    for(auto i:v){
        if(i==node) return true;
    }
    return false;
}

/**
 * @brief Regresa los nodos que se han visitado como string.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param v El vector de visitados.
 * @return string - El string de las visitas.
 */
string Graph::print_visited(vector<int> v){
    stringstream aux;
    aux<<"visited: ";
    for(auto i:v){
        aux<<i<<" ";
    }
    return aux.str();
}

/**
 * @brief Regresa el camino que se tomó para llegar a un nodo.
 * Tiene una complejidad temporal de O(n).
 * 
 * @param path Vector con los caminos para llegar a los nodos.
 * @param start Nodo inicial.
 * @param goal Nodo final.
 * @return string - El string del camino.
 */
string Graph::print_path(vector<vector<int>>& path, int start, int goal){
    int node=path[goal][0];
    stack<int> reverse;
    reverse.push(goal);
    stringstream aux;
    aux<<"path:";
    while(node!=start) {
        reverse.push(node);
        node=path[node][0];
    }
    reverse.push(start);
    while(!reverse.empty()){
        aux<<" "<<reverse.top();
        reverse.pop();
    }
    return aux.str();
}

/**
 * @brief Maneja la función recursiva para explorar los nodos
 * conectados del nodo actual. Tiene una complejidad temporal
 * de O(n+e), n siendo los nodos y e siendo las conexiones.
 * 
 * @param current El nodo actual.
 * @param goal El nodo final.
 * @param st Los próximos nodos a visitar.
 * @param visited Los nodos visitados.
 * @param paths Los caminos para llegar a los nodos.
 * @return string - Los nodos visitados para llegar al final.
 */
string Graph::depthHelper(int current, int goal, stack<int> & st, vector<int> & visited, vector<vector<int>> & paths){
    if(current==goal){
        return print_visited(visited);
    }else if(st.empty()){
        return " node not found";
    }else{
        current=st.top();
        st.pop();
        visited.push_back(current);
        for(int i=0; i<list[current].size(); i++){
            if(!contains(visited, list[current][i])){
                st.push(list[current][i]);
                paths[list[current][i]][0]=current;
            }
        }
        return depthHelper(current, goal, st, visited, paths);
    }
}

/**
 * @brief Busca un nodo por medio de una búsqueda
 * en profundidad. Tiene una complejidad temporal
 * de O(n+e), n siendo los nodos y e siendo las conexiones.
 * 
 * @param start El nodo inicial.
 * @param goal El nodo final.
 * @return string - Los nodos visitados junto con el camino 
 * para llegar al nodo final.
 */
string Graph::DFS(int start, int goal){
    stack<int> st;
    vector<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1,-1));
    st.push(start);
    string s=depthHelper(start, goal, st, visited, paths);
    s=s+print_path(paths, start, goal);
    return s;
}

/**
 * @brief Maneja la función recursiva para explorar los nodos
 * conectados del nodo actual. Tiene una complejidad temporal
 * de O(n+e), n siendo los nodos y e siendo las conexiones.
 * 
 * @param current El nodo actual.
 * @param goal El nodo final.
 * @param qu Los próximos nodos a visitar.
 * @param visited Los nodos visitados.
 * @param paths Los caminos para llegar a los nodos.
 * @return string - Los nodos visitados para llegar al final.
 */
string Graph::breadthHelper(int current, int goal, queue<int> & qu, vector<int> & visited, vector<vector<int>> & paths){
    if(current==goal){
        return print_visited(visited);
    }else if(qu.empty()){
        return " node not found";
    }else{
        current=qu.front();
        qu.pop();
        visited.push_back(current);
        for(int i=0; i<list[current].size(); i++){
            if(!contains(visited, list[current][i]) && paths[list[current][i]][0]==-1){
                qu.push(list[current][i]);
                paths[list[current][i]][0]=current;
            }
        }
        return breadthHelper(current, goal, qu, visited, paths);
    }
}

/**
 * @brief Busca un nodo por medio de una búsqueda
 * en amplitud. Tiene una complejidad temporal
 * de O(n+e), n siendo los nodos y e siendo las conexiones.
 * 
 * @param start El nodo inicial.
 * @param goal El nodo final.
 * @return string - Los nodos visitados junto con el camino 
 * para llegar al nodo final.
 */
string Graph::BFS(int start, int goal){
    queue<int> qu;
    vector<int> visited;
    vector<vector<int>> paths(nodes, vector<int>(1,-1));
    qu.push(start);
    string s=breadthHelper(start, goal, qu, visited, paths);
    s=s+print_path(paths, start, goal);
    return s;
}

#endif