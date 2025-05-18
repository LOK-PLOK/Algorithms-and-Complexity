#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define TRIE_SIZE (ALPHABET_SIZE+1)

typedef struct node{
    struct node* next[TRIE_SIZE];
    int childCount;   // Number of children this node has

}*Trie,trie;

void initTree(Trie* tree);
void initNode(Trie tree);
void insertWord(Trie* tree, char* word);
void deleteWord(Trie* tree, char* word);
int searchWord(Trie tree, char* word);
void displayTrie(Trie tree);

// Stack data structure for non-recursive traversal
typedef struct StackNode {
    Trie node;
    int level;
    int index;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
} Stack;

void initStack(Stack* s);
void push(Stack* s, Trie node, int level, int index);
StackNode* pop(Stack* s);
int isEmpty(Stack* s);

int main() {
    Trie tree;
    initTree(&tree);
    
    // Insert some words
    insertWord(&tree,"apple");
    insertWord(&tree,"apply");
    insertWord(&tree,"app");
    insertWord(&tree,"banana");
    
    // Test search functionality
    printf("Searching for words:\n");
    printf("apple: %s\n", searchWord(tree, "apple") ? "Found" : "Not found");
    printf("apply: %s\n", searchWord(tree, "apply") ? "Found" : "Not found");
    printf("app: %s\n", searchWord(tree, "app") ? "Found" : "Not found");
    printf("banana: %s\n", searchWord(tree, "banana") ? "Found" : "Not found");
    printf("ban: %s\n", searchWord(tree, "ban") ? "Found" : "Not found");
    
    // Display the Trie structure before deletion
    printf("\nTrie structure before deletion:\n");
    displayTrie(tree);
    
    // Delete a word
    printf("\nDeleting 'apple'...\n");
    deleteWord(&tree, "apple");
    
    // Test after deletion
    printf("\nAfter deletion - Searching:\n");
    printf("apple: %s\n", searchWord(tree, "apple") ? "Found" : "Not found");
    printf("apply: %s\n", searchWord(tree, "apply") ? "Found" : "Not found");
    
    // Display the Trie structure after deletion
    printf("\nTrie structure after deletion:\n");
    displayTrie(tree);
    
    // Test more deletions
    printf("\nDeleting 'apply' and 'app'...\n");
    deleteWord(&tree, "apply");
    deleteWord(&tree, "app");
    
    printf("\nAfter more deletions - Trie structure:\n");
    displayTrie(tree);
    
    return 0;
}

void initTree(Trie* tree){
    *tree = NULL;
}

void initNode(Trie tree){
    tree->childCount = 0;
    for(int i = 0; i < TRIE_SIZE; i++){
        tree->next[i] = NULL;  
    }
}

void insertWord(Trie* tree, char* word){
    if(*tree == NULL){
        *tree = (Trie)malloc(sizeof(trie));
        if(*tree != NULL){
            initNode(*tree);
        }
    }
    
    Trie trav = *tree;
    int index,i;
    
    for(i=0;word[i] != '\0';i++){
        index = word[i] - 'a';
        
        if(trav->next[index] == NULL){
            trav->next[index] = (Trie)malloc(sizeof(trie));
            if(trav->next[index] != NULL){
                initNode(trav->next[index]);
                trav->childCount++;
            }
        }
        trav = trav->next[index];
    }
    
    
    if(trav->next[ALPHABET_SIZE] == NULL){
        trav->next[ALPHABET_SIZE] = (Trie)malloc(sizeof(trie));
        if(trav->next[ALPHABET_SIZE] != NULL){
            initNode(trav->next[ALPHABET_SIZE]);
            trav->childCount++;
        }
    }
}

// Search for a word in the trie
// Returns 1 if found, 0 if not found
int searchWord(Trie tree, char* word){
    if(tree == NULL) return 0;
    
    Trie current = tree;
    int index;
    
    // Traverse the trie following the path of the word
    for(int i = 0; word[i] != '\0'; i++){
        index = word[i] - 'a';
        
        // If the path doesn't exist, the word is not in the trie
        if(current->next[index] == NULL)
        return 0;
        
        current = current->next[index];
    }
    
    // Check if this is a complete word (has the terminator node)
    return (current->next[ALPHABET_SIZE] != NULL);
}



// Stack management functions
void initStack(Stack* s) {
    s->top = NULL;
}

void push(Stack* s, Trie node, int level, int index) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) return;
    
    newNode->node = node;
    newNode->level = level;
    newNode->index = index;
    newNode->next = s->top;
    s->top = newNode;
}

StackNode* pop(Stack* s) {
    if (s->top == NULL) return NULL;
    
    StackNode* temp = s->top;
    s->top = s->top->next;
    return temp;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

// Function to display the trie structure - non-recursive version
void displayTrie(Trie tree) {
    if (tree == NULL) return;
    
    Stack stack;
    initStack(&stack);
    
    char prefix[100];  // Buffer for storing current word
    memset(prefix, 0, sizeof(prefix));  // Initialize with zeros
    
    // Push the root node with level 0 and index -1 (indicating root)
    push(&stack, tree, 0, -1);
    
    while (!isEmpty(&stack)) {
        StackNode* current = pop(&stack);
        Trie node = current->node;
        int level = current->level;
        int index = current->index;
        
        // If we came from a letter node (not the root), add it to our prefix
        if (index >= 0 && index < ALPHABET_SIZE) {
            prefix[level-1] = 'a' + index;  // -1 because level is incremented when pushing
            prefix[level] = '\0';  // Ensure null termination
        }
        
        // If this node is the end of a word, print it
        if (node->next[ALPHABET_SIZE] != NULL) {
            printf("Word: %s\n", prefix);
        }
        
        // Push all children to stack (in reverse order to maintain original traversal order)
        for (int i = ALPHABET_SIZE-1; i >= 0; i--) {
            if (node->next[i] != NULL) {
                push(&stack, node->next[i], level+1, i);
            }
        }
        
        free(current);  // Free the stack node after use
    }
}

// PathNode structure to keep track of the path during traversal
typedef struct PathNode {
    Trie* nodePtr;    // Pointer to the node pointer in the trie
    int index;        // Index of this node in its parent's array
    struct PathNode* prev;  // Previous node in path
} PathNode;

void deleteWord(Trie* tree, char* word) {
    if (*tree == NULL || word == NULL || *word == '\0') 
        return;
    
    // Create the first path node (root)
    PathNode* path = (PathNode*)malloc(sizeof(PathNode));
    if (path == NULL) return;
    path->nodePtr = tree;
    path->index = -1;  // Root has no index
    path->prev = NULL;
    
    // Traverse the trie building the path
    Trie* current = tree;
    PathNode* currentPath = path;
    int index;
    
    // Follow the path of the word, building linked list path
    for (int i = 0; word[i] != '\0'; i++) {
        index = word[i] - 'a';
        if (*current == NULL || (*current)->next[index] == NULL) {
            // Word not found, clean up path and return
            while (path != NULL) {
                PathNode* temp = path;
                path = path->prev;
                free(temp);
            }
            return;
        }
        
        // Update current trie position
        current = &((*current)->next[index]);
        
        // Add new node to our path
        PathNode* newNode = (PathNode*)malloc(sizeof(PathNode));
        if (newNode == NULL) {
            // Memory allocation failed, clean up and return
            while (path != NULL) {
                PathNode* temp = path;
                path = path->prev;
                free(temp);
            }
            return;
        }
        
        newNode->nodePtr = current;
        newNode->index = index;
        newNode->prev = currentPath;
        currentPath = newNode;
    }
    
    // Check for terminator node
    if (*current == NULL || (*current)->next[ALPHABET_SIZE] == NULL) {
        // Word not complete in trie, clean up path and return
        while (path != NULL) {
            PathNode* temp = path;
            path = path->prev;
            free(temp);
        }
        return;
    }
    
    // Remove the terminator node and update child count
    free((*current)->next[ALPHABET_SIZE]);
    (*current)->next[ALPHABET_SIZE] = NULL;
    (*current)->childCount--;
    
    // Work backward through the path removing unnecessary nodes
    while (currentPath != NULL && *currentPath->nodePtr != NULL) {
        if ((*currentPath->nodePtr)->childCount == 0) {
            // This node has no children, remove it
            free(*currentPath->nodePtr);
            *currentPath->nodePtr = NULL;
            
            // Update parent's child count if this isn't the root
            if (currentPath->prev != NULL && currentPath->prev->nodePtr != tree) {
                Trie parent = *currentPath->prev->nodePtr;
                parent->childCount--;
            }
        } else {
            // Node still has other children, stop deletion
            break;
        }
        
        // Move up the path
        PathNode* temp = currentPath;
        currentPath = currentPath->prev;
        free(temp);
    }
    
    // Clean up any remaining path nodes
    while (currentPath != NULL) {
        PathNode* temp = currentPath;
        currentPath = currentPath->prev;
        free(temp);
    }
}