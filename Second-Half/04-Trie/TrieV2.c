#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    char letter;
    struct node* nextLetter;
    struct node* newWord;
}*Trie,trie;

void initTree(Trie* tree);
void initNode(Trie tree);
void insertWord(Trie* tree,char* word);
int searchWord(Trie tree, char* word);
int deleteWord(Trie* tree, char* word);
void displayTrie(Trie tree);

int main(){
    Trie tree;
    initTree(&tree);
    // Insert some words
    insertWord(&tree,"apple");
    insertWord(&tree,"apply");
    insertWord(&tree,"application");
    insertWord(&tree,"app");
    insertWord(&tree,"banana");
    
    // Test search functionality
    printf("Searching for words:\n");
    printf("apple: %s\n", searchWord(tree, "apple") ? "Found" : "Not found");
    printf("apply: %s\n", searchWord(tree, "apply") ? "Found" : "Not found");
    printf("app: %s\n", searchWord(tree, "app") ? "Found" : "Not found");
    printf("banana: %s\n", searchWord(tree, "banana") ? "Found" : "Not found");
    printf("ban: %s\n", searchWord(tree, "ban") ? "Found" : "Not found");
    
    // Delete a word
    printf("\nDeleting 'apple'...\n");
    deleteWord(&tree, "apple");
    // Display the Trie structure before deletion
    printf("\nTrie structure before deletion:\n");
    displayTrie(tree);
    
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
    
    // Display the Trie structure after more deletions
    printf("\nAfter more deletions - Trie structure:\n");
    displayTrie(tree);
    
    printf("\nAfter more deletions - Trie structure:\n");
    displayTrie(tree);
    
    return 0;
}

void initTree(Trie* tree){
    *tree = NULL;
}

void initNode(Trie tree){
    tree->letter = '\0';
    tree->newWord = tree->nextLetter = NULL;
}

void insertWord(Trie* tree,char* word){
if (word == NULL || *word == '\0') {
        return;
    }
    
    Trie* trav = tree;
    int i;
    
    // Process each character in the word
    for (i = 0; word[i] != '\0'; i++) {
        // Search for the current character in the current level
        while (*trav != NULL && (*trav)->letter != word[i]) {
            trav = &((*trav)->newWord);
        }
        
        // If character doesn't exist at this level, create it
        if (*trav == NULL) {
            Trie temp = (Trie)malloc(sizeof(trie));
            if (temp != NULL) {
                initNode(temp);
                temp->letter = word[i];
                *trav = temp;
            }
        }
        
        // Move to the next letter position
        trav = &((*trav)->nextLetter);
    }
    
    // Add end-of-word marker if it doesn't already exist
    while (*trav != NULL && (*trav)->letter != '\0') {
        trav = &((*trav)->newWord);
    }
    
    if (*trav == NULL) {
        Trie temp = (Trie)malloc(sizeof(trie));
        if (temp != NULL) {
            initNode(temp);
            // '\0' is already set by initNode
            *trav = temp;
        }
    }
}

int searchWord(Trie tree, char* word) {
    int i;
    Trie trav = tree;
    int found = 0;
    
    // Only proceed if we have a valid tree and word
    if (tree != NULL && word != NULL) {
        // Flag to track if we've successfully followed the entire word path
        int validPath = 1;
        
        // Search for each character in the word
        for (i = 0; word[i] != '\0' && validPath; i++) {
            // Find node for current letter
            while (trav != NULL && trav->letter != word[i]) {
                trav = trav->newWord;
            }
            
            // If we can't find the letter, the word is not in the trie
            if (trav == NULL) {
                validPath = 0;
            } else {
                // Move to next letter
                trav = trav->nextLetter;
            }
        }
        
        // After processing the word, check if there's an end-of-word marker
        if (validPath && trav != NULL) {
            while (trav != NULL && !found) {
                if (trav->letter == '\0') {  // Found end-of-word marker
                    found = 1;
                } else {
                    trav = trav->newWord;
                }
            }
        }
    }
    
    return found;
}

// Recursive function to delete a word from the trie
// Returns 1 if the node should be deleted, 0 otherwise
int deleteWord(Trie* tree, char* word) {
    int shouldDelete = 0;
    
    // Only proceed if we have valid inputs
    if (tree != NULL && *tree != NULL && word != NULL) {
        // End of word reached
        if (*word == '\0') {
            // Find the end marker in the list of alternative letters
            Trie* trav = tree;
            while (*trav != NULL && (*trav)->letter != '\0') {
                trav = &((*trav)->newWord);
            }
            
            // If end marker found, delete it
            if (*trav != NULL) {
                Trie temp = *trav;
                *trav = (*trav)->newWord;
                free(temp);
                
                // Determine whether the parent node should also be deleted
                // (if it has no children)
                shouldDelete = (*tree == NULL || 
                              ((*tree)->nextLetter == NULL && (*tree)->newWord == NULL));
            }
        } else {
            // Find the node for current letter
            Trie* trav = tree;
            while (*trav != NULL && (*trav)->letter != *word) {
                trav = &((*trav)->newWord);
            }
            
            // If letter found, process the next letter
            if (*trav != NULL) {
                // Recurse with next letter
                if (deleteWord(&((*trav)->nextLetter), word + 1)) {
                    // If next letter's node was deleted and current node has no children
                    if ((*trav)->nextLetter == NULL && (*trav)->newWord == NULL) {
                        free(*trav);
                        *trav = NULL;
                        shouldDelete = 1; // This node can be deleted too
                    }
                }
            }
        }
    }
    
    return shouldDelete;
}

void displayTrieHelper(Trie node, char* prefix, int level) {
    if (node == NULL) {
        return;
    }
    
    // Make a copy of the current prefix
    char newPrefix[100]; // Assuming reasonable word length limit
    strcpy(newPrefix, prefix);
    
    // If it's not an end-of-word marker
    if (node->letter != '\0') {
        newPrefix[level] = node->letter;
        newPrefix[level + 1] = '\0';
    } else {
        printf("Word: %s\n", prefix);
    }
    
    // Explore next letter (deeper level)
    displayTrieHelper(node->nextLetter, newPrefix, level + 1);
    
    // Explore alternative letters at same level
    displayTrieHelper(node->newWord, prefix, level);
}

void displayTrie(Trie tree) {
    char prefix[100] = {0}; // Buffer to build words
    displayTrieHelper(tree, prefix, 0);
}
