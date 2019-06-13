#ifndef RBTREE_H
#define RBTREE_H

enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
    int data;
    int color;
    Node *left, *right, *parent;
    Node(int);

};

class RBTree
{
public:
	Node * root;
	RBTree();
	void rotateLeft(Node *&);
	void rotateRight(Node *&);
	Node* findMin(Node* node){
	void fixDeleteRBTree(Node *&node) {
	Node * deleteBST(Node *&node, int data){
	void deleteRB(int data){

};
#endif