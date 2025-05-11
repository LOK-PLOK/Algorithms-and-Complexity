#include "../../utilities/general.h"
#include "../../utilities/arrays.h"

typedef struct node{
    int data;
    struct node* Left;
    struct node* Right;
}* BST;

void initTree(BST* tree);
void populate(int* arr,int size,BST* tree);
void insertV1(BST* tree,int x);
void insertV2(BST* tree,int x);

// Search operations
BST search(BST tree, int x);
int isMember(BST tree, int x);

// Delete operation
void delete(BST* tree, int x);

// Traversals
void preorder(BST tree);
void inorder(BST tree);
void postorder(BST tree);

// Clean
void clean(BST* tree);

int main(){
    system("cls");
    BST tree;
    initTree(&tree);
    int arr[10];
    printf("Elements: ");
    for(int i = 0; i< 10; i++){
        arr[i] = rand() % 10;
        printf("%d ", arr[i]); 
    }
    printf("\n\n"); 
    
    populate(arr,10,&tree);
    printf("PreOrder: ");
    preorder(tree);
    printf("\n");
    
    printf("InOrder: ");
    inorder(tree);
    printf("\n");
    
    printf("PostOrder: ");
    postorder(tree);
    printf("\n\n");
    
    // Demonstrate search and isMember
    int searchValue = arr[3]; // Use a value from our array to ensure it exists
    printf("Searching for %d: %s\n", searchValue, 
           isMember(tree, searchValue) ? "Found" : "Not Found");
    
    // Demonstrate deletion
    printf("Deleting %d...\n", searchValue);
    delete(&tree, searchValue);
    
    printf("InOrder after deletion: ");
    inorder(tree);
    printf("\n");
    
    // Verify the element is gone
    printf("Searching for %d after deletion: %s\n\n", searchValue,
           isMember(tree, searchValue) ? "Found" : "Not Found");
    
    clean(&tree);
    return 0;
}

void initTree(BST* tree){
    *tree = NULL;
}

void populate(int* arr,int size,BST* tree){
    for(int i = 0;i<size;i++){
        insertV1(tree,arr[i]);
    }
}

void insertV1(BST* tree,int x){
    BST* trav,temp;
    temp = (BST)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->data = x;
        temp->Left = temp->Right = NULL;
    }
    
    for(trav = tree; *trav != NULL; trav = (x < (*trav)->data)? 
    &(*trav)->Left:&(*trav)->Right){}
    
    *trav = temp;
}

void insertV2(BST* tree,int x){
    
}

void preorder(BST tree){
    if(tree == NULL){
        return;
    }
    printf("%d ",tree->data);
    preorder(tree->Left);
    preorder(tree->Right);
}

void inorder(BST tree){
    if(tree == NULL){
        return;
    }
    inorder(tree->Left);
    printf("%d ",tree->data);
    inorder(tree->Right);
}

void postorder(BST tree){
    if(tree == NULL){
        return;
    }
    postorder(tree->Left);
    postorder(tree->Right);
    printf("%d ",tree->data);
}

void clean(BST* tree){
    if(*tree != NULL){
        clean(&(*tree)->Left);
        clean(&(*tree)->Right);
        free(*tree);
        *tree = NULL;
    }
}

BST search(BST tree, int x){
    if(tree == NULL || tree->data == x){
        return tree;
    }
    
    if(x < tree->data){
        return search(tree->Left, x);
    } else {
        return search(tree->Right, x);
    }
}

int isMember(BST tree, int x){
    return search(tree, x) != NULL;
}

void delete(BST* tree, int x){
    BST* trav;
    BST temp, successor;
    
    for(trav = tree; *trav != NULL && (*trav)->data != x; 
        trav = (x < (*trav)->data) ? &(*trav)->Left : &(*trav)->Right){}
    
    if(*trav == NULL){
        return;
    }
      temp = *trav; 
    
    // Case 1: Node has at most one child (left or right)
    if(temp->Left == NULL){
        *trav = temp->Right;  // This handles both no children and right child only
    }
    // Case 2: Node has only left child or two children
    else if(temp->Right == NULL){
        *trav = temp->Left;   // This handles the left child only case
    }
    // Case 3: Node has two children (temp->Left != NULL && temp->Right != NULL)
    else {
        // Find inorder successor (smallest node in right subtree)
        BST* succPtr;
        for(succPtr = &temp->Right; (*succPtr)->Left != NULL; 
            succPtr = &(*succPtr)->Left){}
        
        successor = *succPtr;
        
        // Replace succPtr with its right child (if any)
        *succPtr = successor->Right;
        
        // Replace node to be deleted with successor
        successor->Left = temp->Left;
        successor->Right = temp->Right;
        *trav = successor;
    }
    
    // Free memory of deleted node
    free(temp);
}