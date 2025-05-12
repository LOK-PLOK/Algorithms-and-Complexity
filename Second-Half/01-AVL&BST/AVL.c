#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>



typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    int height;
}* AVL;

int MIN(int a, int b){
    return (a < b) ? a : b;
}

int MAX(int a, int b){
    return (a > b) ? a : b;
}


void init(AVL* tree);
AVL create(int key);
int height(AVL node);
void updateHeight(AVL node);
AVL rightRotate(AVL y);
AVL leftRotate(AVL x);
int getBalance(AVL node);
AVL insert(AVL node, int key);
AVL deleteNode(AVL root, int key);
AVL minValueNode(AVL node);


// operations
int searchV1(AVL tree, int key);
int searchV2(AVL tree, int key);


int main(){
    
    
    return 0;
}

void init(AVL* tree){
    *tree = NULL;
}

AVL create(int key){
    AVL temp = (AVL)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->data = key;
        temp->left = temp->right = 0;
        temp->height = 1;
    }
    
    return temp;
}

int height(AVL node){
    return (node == NULL)? 0:node->height;
}

void updateHeight(AVL node){
    if(node != NULL){
        node->height = 1+ MAX(height(node->left),height(node->right));
    }
}

AVL rightRotate(AVL y){
    AVL x = y->left;
    AVL T2 = x->right;

    //rotation
    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVL leftRotate(AVL x){
    AVL y = x->right;
    AVL T2 = y->left;

    //rotation
    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}


// search by Recursive method
int searchV1(AVL tree, int key){
    if(tree == NULL){
        return -999; 
    } else if(tree->data == key){
        return tree->data;
    } else if(key < tree->data){
        return searchV1(tree->left, key);
    } else {
        return searchV1(tree->right, key);
    }
}

// Search by Iterative method
int searchV2(AVL tree, int key){
    AVL trav;
    for(trav = tree; trav != NULL && trav->data != key;trav = (key < trav->data)? trav->left:trav->right){}
    
    return (trav != NULL)? trav->data:-999;
}

// Get balance factor of a node
int getBalance(AVL node) {
    return (node == NULL)? 0:(height(node->left) - height(node->right));
}

// Insert a key into the AVL tree
AVL insert(AVL node, int key) {
    // 1. Perform standard BST insertion
    if (node == NULL)
        return create(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else // Duplicate keys not allowed
        return node;

    // 2. Update height of this ancestor node
    updateHeight(node);

    // 3. Get the balance factor of this ancestor node to check if it became unbalanced
    int balance = getBalance(node);

    // 4. If the node becomes unbalanced, there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Find the node with minimum value in a BST
AVL minValueNode(AVL node) {
    AVL current = node;

    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Delete a node from the AVL tree
AVL deleteNode(AVL root, int key) {
    // STEP 1: Standard BST delete
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->data)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    // If key is same as root's key, then this is the node to be deleted
    else {
        // Node with only one child or no child
        if (root->left == NULL) {
            AVL temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            AVL temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        AVL temp = minValueNode(root->right);

        // Copy the inorder successor's data to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }

    // If the tree had only one node then return
    if (root == NULL)
        return root;

    // STEP 2: Update height of the current node
    updateHeight(root);

    // STEP 3: Get the balance factor
    int balance = getBalance(root);

    // STEP 4: If unbalanced, consider the 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}
