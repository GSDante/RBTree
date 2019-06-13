#include <iostream>

Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

RBTree() {
    root = nullptr;
}

int getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;

    return node->color;
}

void setColor(Node *&node, int color) {
    if (node == nullptr)
        return;

    node->color = color;
}

void rotateLeft(Node *&ptr){
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

void rotateRight(Node *&ptr){
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