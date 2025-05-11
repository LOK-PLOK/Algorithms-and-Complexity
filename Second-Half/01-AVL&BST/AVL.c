#include "../../utilities/general.h"
#include "../../utilities/arrays.h"

typedef struct node{
    int data;
    struct node* Left;
    struct node* Right;
    int height;
}* AVL;

// Function prototypes
void initTree(AVL* tree);
int height(AVL node);
int getBalance(AVL node);
AVL createNode(int data);
int max(int a, int b);
AVL rightRotate(AVL y);
AVL leftRotate(AVL x);
AVL search(AVL tree, int key);
AVL insert(AVL tree, int key);
AVL delete(AVL tree, int key);
AVL minValueNode(AVL node);
void preOrder(AVL tree);
void inOrder(AVL tree);
void postOrder(AVL tree);
void displayTree(AVL tree, int level);
void freeTree(AVL tree);

int main(){
    // Initialize AVL tree
    AVL tree = NULL;
    
    // Insert elements
    printf("Inserting elements: 10, 20, 30, 40, 50, 25\n");
    tree = insert(tree, 10);
    tree = insert(tree, 20);
    tree = insert(tree, 30);
    tree = insert(tree, 40);
    tree = insert(tree, 50);
    tree = insert(tree, 25);
    
    // Display the tree
    printf("\nAVL Tree after insertions:\n");
    displayTree(tree, 0);
    
    printf("\nInorder traversal: ");
    inOrder(tree);
    printf("\n");
    
    // Demonstrate search
    int searchKey = 30;
    printf("\nSearching for %d: ", searchKey);
    AVL result = search(tree, searchKey);
    if(result != NULL)
        printf("Found\n");
    else
        printf("Not found\n");
    
    // Demonstrate deletion
    printf("\nDeleting %d\n", searchKey);
    tree = delete(tree, searchKey);
    
    printf("\nAVL Tree after deletion:\n");
    displayTree(tree, 0);
    
    printf("\nInorder traversal after deletion: ");
    inOrder(tree);
    printf("\n");
    
    // Free the tree
    freeTree(tree);
    
    return 0;
}

// Initialize an empty AVL tree
void initTree(AVL* tree) {
    *tree = NULL;
}

// Get height of the node
int height(AVL node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Get balance factor of a node
int getBalance(AVL node) {
    if (node == NULL)
        return 0;
    return height(node->Left) - height(node->Right);
}

// Create a new AVL tree node
AVL createNode(int data) {
    AVL newNode = (AVL)malloc(sizeof(struct node));
    if (newNode != NULL) {
        newNode->data = data;
        newNode->Left = NULL;
        newNode->Right = NULL;
        newNode->height = 1;  // New node is initially at height 1
    }
    return newNode;
}

// Right rotate subtree rooted with y
AVL rightRotate(AVL y) {
    AVL x = y->Left;
    AVL T2 = x->Right;
    
    // Perform rotation
    x->Right = y;
    y->Left = T2;
    
    // Update heights
    y->height = max(height(y->Left), height(y->Right)) + 1;
    x->height = max(height(x->Left), height(x->Right)) + 1;
    
    // Return new root
    return x;
}

// Left rotate subtree rooted with x
AVL leftRotate(AVL x) {
    AVL y = x->Right;
    AVL T2 = y->Left;
    
    // Perform rotation
    y->Left = x;
    x->Right = T2;
    
    // Update heights
    x->height = max(height(x->Left), height(x->Right)) + 1;
    y->height = max(height(y->Left), height(y->Right)) + 1;
    
    // Return new root
    return y;
}

// SEARCH: Find a node with a given key in the AVL tree
AVL search(AVL tree, int key) {
    // Base case: root is null or key is present at root
    if (tree == NULL || tree->data == key)
        return tree;
    
    // Key is greater than root's key, search in right subtree
    if (key > tree->data)
        return search(tree->Right, key);
    
    // Key is smaller than root's key, search in left subtree
    return search(tree->Left, key);
}

// INSERT: Insert a new node with given key in the AVL tree
AVL insert(AVL tree, int key) {
    // Standard BST insertion
    if (tree == NULL)
        return createNode(key);
    
    if (key < tree->data)
        tree->Left = insert(tree->Left, key);
    else if (key > tree->data)
        tree->Right = insert(tree->Right, key);
    else // Duplicate keys not allowed
        return tree;
    
    // Update height of this ancestor node
    tree->height = 1 + max(height(tree->Left), height(tree->Right));
    
    // Get the balance factor to check if this node became unbalanced
    int balance = getBalance(tree);
    
    // Left Left Case
    if (balance > 1 && key < tree->Left->data)
        return rightRotate(tree);
    
    // Right Right Case
    if (balance < -1 && key > tree->Right->data)
        return leftRotate(tree);
    
    // Left Right Case
    if (balance > 1 && key > tree->Left->data) {
        tree->Left = leftRotate(tree->Left);
        return rightRotate(tree);
    }
    
    // Right Left Case
    if (balance < -1 && key < tree->Right->data) {
        tree->Right = rightRotate(tree->Right);
        return leftRotate(tree);
    }
    
    // Return the unchanged node pointer
    return tree;
}

// Find the node with minimum value in AVL tree
AVL minValueNode(AVL node) {
    AVL current = node;
    
    // Loop down to find the leftmost leaf
    while (current->Left != NULL)
        current = current->Left;
    
    return current;
}

// DELETE: Delete a node with the given key from the AVL tree
AVL delete(AVL tree, int key) {
    // Standard BST delete
    if (tree == NULL)
        return tree;
    
    // If the key to be deleted is smaller, it's in left subtree
    if (key < tree->data)
        tree->Left = delete(tree->Left, key);
    
    // If the key to be deleted is greater, it's in right subtree
    else if (key > tree->data)
        tree->Right = delete(tree->Right, key);
    
    // If key is same as root's key, this is the node to be deleted
    else {
        // Node with only one child or no child
        if ((tree->Left == NULL) || (tree->Right == NULL)) {
            AVL temp = tree->Left ? tree->Left : tree->Right;
            
            // No child case
            if (temp == NULL) {
                temp = tree;
                tree = NULL;
            } else // One child case
                *tree = *temp; // Copy the contents of the non-empty child
            
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVL temp = minValueNode(tree->Right);
            
            // Copy the inorder successor's data to this node
            tree->data = temp->data;
            
            // Delete the inorder successor
            tree->Right = delete(tree->Right, temp->data);
        }
    }
    
    // If the tree had only one node then return
    if (tree == NULL)
        return tree;
    
    // Update height of the current node
    tree->height = 1 + max(height(tree->Left), height(tree->Right));
    
    // Get the balance factor
    int balance = getBalance(tree);
    
    // If unbalanced, there are 4 cases
    
    // Left Left Case
    if (balance > 1 && getBalance(tree->Left) >= 0)
        return rightRotate(tree);
    
    // Left Right Case
    if (balance > 1 && getBalance(tree->Left) < 0) {
        tree->Left = leftRotate(tree->Left);
        return rightRotate(tree);
    }
    
    // Right Right Case
    if (balance < -1 && getBalance(tree->Right) <= 0)
        return leftRotate(tree);
    
    // Right Left Case
    if (balance < -1 && getBalance(tree->Right) > 0) {
        tree->Right = rightRotate(tree->Right);
        return leftRotate(tree);
    }
    
    return tree;
}

// Print the tree in preOrder traversal
void preOrder(AVL tree) {
    if (tree != NULL) {
        printf("%d ", tree->data);
        preOrder(tree->Left);
        preOrder(tree->Right);
    }
}

// Print the tree in inOrder traversal (sorted)
void inOrder(AVL tree) {
    if (tree != NULL) {
        inOrder(tree->Left);
        printf("%d ", tree->data);
        inOrder(tree->Right);
    }
}

// Print the tree in postOrder traversal
void postOrder(AVL tree) {
    if (tree != NULL) {
        postOrder(tree->Left);
        postOrder(tree->Right);
        printf("%d ", tree->data);
    }
}

// Display tree structure visually
void displayTree(AVL tree, int level) {
    if(tree == NULL) return;
    
    // Process right child (higher values)
    displayTree(tree->Right, level + 1);
    
    // Print current node with indentation based on level
    for(int i = 0; i < level; i++)
        printf("    ");
    printf("%d\n", tree->data);
    
    // Process left child (lower values)
    displayTree(tree->Left, level + 1);
}

// Free the memory allocated for the tree
void freeTree(AVL tree) {
    if (tree != NULL) {
        freeTree(tree->Left);
        freeTree(tree->Right);
        free(tree);
    }
}