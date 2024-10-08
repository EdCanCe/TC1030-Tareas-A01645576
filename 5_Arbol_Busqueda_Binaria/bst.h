#ifndef BST_H
#define BST_H

template <class T> class BST;

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

template <class T>
TreeNode<T>::TreeNode(T val) {
	value=val;
	left=0;
	right=0;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T>* le, TreeNode<T>* ri) {
	value=val;
	left=le;
	right=ri;
}

template <class T>
void TreeNode<T>::add(T val) { //Complejidad temporal: O(n) - Si fuera degenerado
	if(val > value){
		if(right!=0) right->add(val);
		else right=new TreeNode(val);
	}else{
		if(left!=0) left->add(val);
		else left=new TreeNode(val);
	}
}

template <class T>
int TreeNode<T>::height() { //Complejidad temporal: O(n) - Revisa todo siempre
    int aux=1;
	if(left!=0) aux=std::max(aux, left->height()+1); 
    if(right!=0) aux=std::max(aux, right->height()+1); 
    return aux;
}

template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T x){ //Complejidad temporal: O(n) - Si fuera degenerado
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

template <class T>
int TreeNode<T>::level(T x){ //Complejidad temporal: O(n) - Si fuera degenerado
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

template <class T>
BST<T>::BST(){
    root=0;
}

template <class T>
bool BST<T>::empty() const{
    return root==0;
}

template<class T>
void BST<T>::add(T x) { //Complejidad temporal: O(n) - Si fuera degenerado
	if(empty()) root=new TreeNode(x);
	else root->add(x);
}

template<class T>
std::string BST<T>::visit(){ //Complejidad temporal: O(n) - Si fuera degenerado
    std::string pre=preorder(), in=inorder(), pos=postorder();
    std::stringstream aux;
    aux<<pre<<"\n"<<in<<"\n"<<pos<<"\n"<<pre;
    return aux.str();
}

template<class T>
int BST<T>::height(){ //Complejidad temporal: O(n) - Revisa todo
    if(!empty()){
        return root->height();
    }
    return -1;
}

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

template<class T>
int BST<T>::whatlevelamI(T x){ //Complejidad temporal: O(n) - Si fuera degenerado
    if(!empty()){
        return root->level(x);
    }
    return -1;
}

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