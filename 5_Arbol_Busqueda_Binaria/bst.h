/**
*
* Edmundo Canedo Cervantes
* A01645576
*
*/
#ifndef BST_H
#define BST_H

template <class T> class BST;

/**
 * @brief Clase que contiene los métodos
 * y atributosNodos usados por el árbol.
 */
template <class T>
class TreeNode{
    private:
        T value;
        TreeNode<T>* left;
        TreeNode<T>* right;

        TreeNode(T);
        TreeNode(T, TreeNode<T>*, TreeNode<T>*);

        void add(T);
        int height();
        void ancestors(std::stringstream&, T);
        int level(T);

	    void preorder(std::stringstream&) const;
        void inorder(std::stringstream&) const;
        void postorder(std::stringstream&) const;

        friend class BST<T>;
};

/**
 * @brief Constructor de un nodo con solo su valor.
 * 
 * @param val Valor del nodo.
 */
template <class T>
TreeNode<T>::TreeNode(T val) {
	value=val;
	left=0;
	right=0;
}

/**
 * @brief Constructor del nodo con sus valores e hijos.
 * 
 * @param val Valor del nodo.
 * @param le Hijo izquierdo.
 * @param ri Hijo derecho.
 */
template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T>* le, TreeNode<T>* ri) {
	value=val;
	left=le;
	right=ri;
}

/**
 * @brief Añade un elemento al nodo. 
 * Como lo puede añadir en sus hijos y puede
 * ser degenerado tiene una complejidad
 * temporal de O(n).
 * 
 * @param val - El valor a añadir.
 */
template <class T>
void TreeNode<T>::add(T val) { 
	if(val > value){
		if(right!=0) right->add(val);
		else right=new TreeNode(val);
	}else{
		if(left!=0) left->add(val);
		else left=new TreeNode(val);
	}
}

/**
 * @brief Obtiene la altura del nodo. Ya que
 * lo busca en todos sus hijos tiene una complejidad
 * temporal de O(n).
 * 
 * @return int - La altura del nodo.
 */
template <class T>
int TreeNode<T>::height() {
    int aux=1;
	if(left!=0) aux=std::max(aux, left->height()+1); 
    if(right!=0) aux=std::max(aux, right->height()+1); 
    return aux;
}

/**
 * @brief Encuentra el camino que se recorre 
 * para encontrar un nodo en específico. Debido
 * a que el árbol puede degenerarse tiene una
 * complejidad temporal de O(n).
 * 
 * @param aux Donde se guardará el camino
 * @param x El valor a buscar.
 */
template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T x){
	aux << value;
	if(x>value && right!=0 && right->value!=x){
        aux<<" ";
        right->ancestors(aux, x);
    }
    if(x<value && left!=0 && left->value!=x){
        aux<<" ";
        left->ancestors(aux, x);
    }
    if(left==0 && right==0 && value!=x){
        aux.str("");
        aux<<"[";
    }
}

/**
 * @brief Encuentra el nivel en el cuál se
 * encuentra un nodo en específico. 1 siendo
 * ese mismo nivel. Tiene una complejidad de O(n)
 * ya que el árbol podría estar degenerado.
 * 
 * @param x El nodo a buscar
 * @return int - El nivel del nodo.
 */
template <class T>
int TreeNode<T>::level(T x){
    if(value==x) return 1;
	if(x>value){
        if(right!=0){
            return right->level(x)+1;
        }
    }
    if(x<value){
        if(left!=0){
            return left->level(x)+1;
        }
    }
    return -1;
}

/**
 * @brief Realiza un recorrido en preorden al árbol.
 * Guarda los valores de los nodos recorridos en el
 * stringstream para que pueda imprimirse. Tiene una
 * complejidad temporal de O(n).
 * 
 * @param aux Donde se guarda el recorrido.
 */
template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const { //Complejidad temporal: O(n) - Revisa todo
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

/**
 * @brief Realiza un recorrido en orden al árbol.
 * Guarda los valores de los nodos recorridos en el
 * stringstream para que pueda imprimirse. Tiene una
 * complejidad temporal de O(n).
 * 
 * @param aux Donde se guarda el recorrido.
 */
template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const { //Complejidad temporal: O(n) - Revisa todo
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

/**
 * @brief Realiza un recorrido en postorden al árbol.
 * Guarda los valores de los nodos recorridos en el
 * stringstream para que pueda imprimirse. Tiene una
 * complejidad temporal de O(n).
 * 
 * @param aux Donde se guarda el recorrido.
 */
template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const { //Complejidad temporal: O(n) - Revisa todo
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
    if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}

/**
 * @brief Declaración de la clase BST donde se
 * tienen sus métodos y atributos.
 */
template <class T>
class BST{
    private:
        TreeNode<T>* root;

    public:
        BST();
        bool empty() const;
        void add(T);
        std::string visit();
        int height();
        std::string ancestors(T);
        int whatlevelamI(T);

	    std::string preorder() const;
        std::string inorder() const;
        std::string postorder() const;
};

/**
 * @brief Constructor del árbol.
 */
template <class T>
BST<T>::BST(){
    root=0;
}

/**
 * @brief Verifica si el árbol está vacío.
 * 
 * @return TRUE - El árbol está vacío | FALSE
 * - El árbol aún tiene valores.
 */
template <class T>
bool BST<T>::empty() const{
    return root==0;
}

/**
 * @brief Añade un elemento al nodo. 
 * Tiene una complejidad temporal de O(n).
 * 
 * @param val - El valor a añadir.
 */
template<class T>
void BST<T>::add(T x) {
	if(empty()) root=new TreeNode(x);
	else root->add(x);
}

/**
 * @brief Imprime el árbol con los diferentes
 * recorridos que puede tomar. Tiene una
 * complejidad de O(n),
 * 
 * @return std::string - El árbol en forma de
 * string.
 */
template<class T>
std::string BST<T>::visit(){ //Complejidad temporal: O(n) - Si fuera degenerado
    std::string pre=preorder(), in=inorder(), pos=postorder();
    std::stringstream aux;
    aux<<pre<<"\n"<<in<<"\n"<<pos<<"\n"<<pre;
    return aux.str();
}

/**
 * @brief Obtiene la altura del árbol. Ya que
 * lo busca en todos sus hijos tiene una complejidad
 * temporal de O(n).
 * 
 * @return int - La altura del árbol.
 */
template<class T>
int BST<T>::height(){ //Complejidad temporal: O(n) - Revisa todo
    if(!empty()){
        return root->height();
    }
    return -1;
}

/**
 * @brief Encuentra el camino que se recorre 
 * para encontrar un nodo en específico. Debido
 * a que el árbol puede degenerarse tiene una
 * complejidad temporal de O(n).
 * 
 * @param x El valor a buscar.
 */
template<class T>
std::string BST<T>::ancestors(T x){ //Complejidad temporal: O(n) - Si fuera degenerado
    std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->ancestors(aux, x);
	}
	aux << "]";
	return aux.str();
}

/**
 * @brief Encuentra el nivel en el cuál se
 * encuentra un nodo en específico. 1 siendo
 * ese mismo nivel. Tiene una complejidad de O(n)
 * ya que el árbol podría estar degenerado.
 * 
 * @param x El nodo a buscar
 * @return int - El nivel del nodo.
 */
template<class T>
int BST<T>::whatlevelamI(T x){ //Complejidad temporal: O(n) - Si fuera degenerado
    if(!empty()){
        return root->level(x);
    }
    return -1;
}

/**
 * @brief Realiza un recorrido en preorden al árbol.
 * Tiene una complejidad temporal de O(n).
 */
template <class T>
std::string BST<T>::preorder()const{ //Complejidad temporal: O(n) - Revisa todo
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->preorder(aux);
	}
	aux << "]";
	return aux.str();
}

/**
 * @brief Realiza un recorrido en orden al árbol.
 * Tiene una complejidad temporal de O(n).
 */
template <class T>
std::string BST<T>::inorder()const{ //Complejidad temporal: O(n) - Revisa todo
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->inorder(aux);
	}
	aux << "]";
	return aux.str();
}

/**
 * @brief Realiza un recorrido en postorden al árbol.
 * Tiene una complejidad temporal de O(n).
 */
template <class T>
std::string BST<T>::postorder()const{ //Complejidad temporal: O(n) - Revisa todo
	std::stringstream aux;

	aux << "[";
	if (!empty()) {
		root->postorder(aux);
	}
	aux << "]";
	return aux.str();
}

#endif