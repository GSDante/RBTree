#include <iostream>

Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

RBTree::RBTree() {
    root = nullptr;
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

void RBTree::rotateLeft(Node *&ptr){
	// Criação do nó do filho direito tendo em vista que será
	// o filho direito do nó desbalanceado que irá ser o novo pai
	Node *child_right = ptr->right;
	ptr->right = child_right->left;

	// Após o neto esquerdo passar a ser o filho direito
	// o neto aponta para o avô
	if(ptr->right != nullptr){
		ptr->right->parent = ptr;
	}
	// 
	child_right->parent = ptr->parent;
	// caso o avô fosse um nó raiz, então o filho direito passa a ser raiz
	if(ptr->parent == nullptr){
		root = child_right;
	// o pai de ptr aponta para o antigo filho direito
	}else if(ptr == ptr->parent->left ){
		ptr->parent->left = child_right;
	}else{
		ptr->parent->right = child_right;
	}
	// o ponteiro pai do filho direito aponta para o antigo avô
	child_right->left = ptr;
	ptr->parent = child_right;
}

void RBTree::rotateRight(Node *&ptr){
	Node * child_left = ptr->left;
	ptr->left = child_left->right;

	if(ptr->left != nullptr){
		ptr->left->parent = ptr;
	}
	// 
	child_left->parent = ptr->parent;
	// caso o avô fosse um nó raiz, então o filho direito passa a ser raiz
	if(ptr->parent == nullptr){
		root = child_left;
	// o pai de ptr aponta para o antigo filho direito
	}else if(ptr == ptr->parent->left ){
		ptr->parent->left = child_left;
	}else{
		ptr->parent->right = child_left;
	}
	// o ponteiro pai do filho direito aponta para o antigo avô
	child_left->left = ptr;
	ptr->parent = child_left;
}
// função auxiliar da remoção
Node* RBTree::findMin(Node* node){
	
	if(node == nullptr)
	{
		return node;
	} 

	while( node->left != nullptr )
	{
		node = node->left;
	}

	return node;
} 

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;

    if (node == root) {
        root = nullptr;
        return;
    }
    // caso o nó seja vermelho ou qualquer um dos dois filhos sejam vermelhos
    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
    	Node *child; 
    	
    	if(node->left != nullptr){
    		child = node->left;
    	}else{
    		child = node->right;
    	}
    	// se for filho esquerdo, então remove o nó e realoca o fico esquerdo dele
    	// e o pinta de preto
    	if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr){
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
        } else {
    	// se for filho direito, então remove o nó e realoca o fico esquerdo dele
    	// e o pinta de preto        	
            node->parent->right = child;
            if (child != nullptr){
                child->parent = node->parent;
            }
            setColor(child, BLACK);
            delete (node);
        }
    }else{
    	//caso todos sejam pretos
    	//aplicação das regras
    	Node *uncle = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                uncle = parent->right;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(uncle->left) == BLACK && getColor(uncle->right) == BLACK) {
                        setColor(uncle, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(uncle->right) == BLACK) {
                            setColor(uncle->left, BLACK);
                            setColor(uncle, RED);
                            rotateRight(uncle);
                            uncle = parent->right;
                        }
                        setColor(uncle, parent->color);
                        setColor(parent, BLACK);
                        setColor(uncle->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                uncle = parent->left;
                if (getColor(uncle) == RED) {
                    setColor(uncle, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(uncle->left) == BLACK && getColor(uncle->right) == BLACK) {
                        setColor(uncle, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(uncle->left) == BLACK) {
                            setColor(uncle->right, BLACK);
                            setColor(uncle, RED);
                            rotateLeft(uncle);
                            uncle = parent->left;
                        }
                        setColor(uncle, parent->color);
                        setColor(parent, BLACK);
                        setColor(uncle->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }

}


// será aplicado a remoção da best e em seguida será consertado 
Node * RBTree::deleteBST(Node *&node, int data){
	if (node == nullptr) root = node; 
  
    if (data < node->data)
    { 
        node->left = remove(node->left, data);
    } 
  
    else if (data > node->data) 
    {
        node->right = remove(node->right, data); 
	}  
  
    else
    { 
        
        if (node->left == nullptr) 
        { 
            Node *temp = node->right; 
            delete node; 
            return temp; 
        } 
        else if (node->right == nullptr) 
        { 
            Node *temp = node->left; 
            delete node; 
            return temp; 
        } 
  
        Node* temp = findMin(node->right); 
  
        node->data = temp->data; 
  
        node->right = remove(node->right, temp->data);
    } 
    return node; 
}

void RBTree::deleteRB(int data){
	 Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}