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