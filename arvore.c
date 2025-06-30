#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key, height;
    struct Node *left, *right;
} Node;

int height(Node* n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* insertAVL(Node* node, int key) {
    if (!node) return newNode(key);
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) return rightRotate(node);
    if (balance < -1 && key > node->right->key) return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* insertBST(Node* node, int key) {
    if (!node) return newNode(key);
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);
    return node;
}

Node* search(Node* root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return search(root->left, key);
    return search(root->right, key);
}

void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void testarTempoInsercao(int n) {
    Node *rootBST = NULL, *rootAVL = NULL;
    clock_t start, end;

    printf("\nInserindo %d elementos...\n", n);

    start = clock();
    for (int i = 0; i < n; i++)
        rootBST = insertBST(rootBST, rand() % (n * 10));
    end = clock();
    printf("Tempo BST: %.4f ms\n", 1000.0 * (end - start) / CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < n; i++)
        rootAVL = insertAVL(rootAVL, rand() % (n * 10));
    end = clock();
    printf("Tempo AVL: %.4f ms\n", 1000.0 * (end - start) / CLOCKS_PER_SEC);

    freeTree(rootBST);
    freeTree(rootAVL);
}

int main() {
    srand(time(NULL));

    testarTempoInsercao(1000);
    testarTempoInsercao(10000);
    testarTempoInsercao(50000);

    return 0;
}