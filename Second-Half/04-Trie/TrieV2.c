#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    char letter;
    struct node* nextLetter;
    struct node* newWord;
}*Trie,trie;

void initTree(Trie* tree);
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

void insertWord(Trie* tree,char* word){
     int i = 0;
    Trie* trav = tree;
    
    // Process each character in the word
    for(i = 0; word[i] != '\0'; i++) {
        // Find node for current letter
        for(; *trav != NULL && (*trav)->letter != word[i]; trav = &(*trav)->newWord) { }
        
        // If node doesn't exist, create it
        if(*trav == NULL) {
            *trav = (Trie)malloc(sizeof(trie));
            if(*trav != NULL) {
                (*trav)->letter = word[i];
                (*trav)->nextLetter = NULL;
                (*trav)->newWord = NULL;
            }
        }
        
        // Move to next letter position
        trav = &(*trav)->nextLetter;
    }
    
    // Mark end of word with an empty node if not already present
    for(; *trav != NULL && (*trav)->letter != '\0'; trav = &(*trav)->newWord) { }
    
    if(*trav == NULL) {
        *trav = (Trie)malloc(sizeof(trie));
        if(*trav != NULL) {
            (*trav)->letter = '\0';  // End of word marker
            (*trav)->nextLetter = NULL;
            (*trav)->newWord = NULL;
        }
    }
    
}

int searchWord(Trie tree, char* word) {
    int i;
    Trie trav = tree;
    
    // Search for each character in the word
    for (i = 0; word[i] != '\0'; i++) {
        // Find node for current letter
        while (trav != NULL && trav->letter != word[i]) {
            trav = trav->newWord;
        }
        
        // If we can't find the letter, the word is not in the trie
        if (trav == NULL) {
            return 0;
        }
        
        // Move to next letter
        trav = trav->nextLetter;
    }
    
    // After processing the word, check if there's an end-of-word marker
    while (trav != NULL) {
        if (trav->letter == '\0') {  // Found end-of-word marker
            return 1;
        }
        trav = trav->newWord;
    }
    
    // No end-of-word marker found
    return 0;
}

// Helper function to check if a node has children
int isNodeEmpty(Trie node) {
    return (node->nextLetter == NULL && node->newWord == NULL);
}

// Helper function for deleteWord, handles recursive deletion
int deleteHelper(Trie* tree, char* word, int depth) {
    // Base case: If tree is empty
    if (*tree == NULL) {
        return 0;
    }
    
    // If last character of word is being processed
    if (word[depth] == '\0') {
        // Found the end-of-word marker
        if ((*tree)->letter == '\0') {
            // If this node has no other branches
            if (isNodeEmpty(*tree)) {
                free(*tree);
                *tree = NULL;
                return 1; // Node deleted
            } else {
                // Node has other branches, just move to next word
                Trie temp = *tree;
                *tree = (*tree)->newWord;
                free(temp);
                return 0; // Node was not completely deleted
            }
        }
        
        // If we are here, then the current node is not end of word
        // Search in alternative words
        Trie* trav = &((*tree)->newWord);
        while (*trav != NULL && (*trav)->letter != '\0') {
            trav = &((*trav)->newWord);
        }
        
        // If end marker found, delete it
        if (*trav != NULL) {
            Trie temp = *trav;
            *trav = (*trav)->newWord;
            free(temp);
            return 0;
        }
        return 0;
    }
    
    // If not the last character, find the node corresponding to current character
    Trie* trav = tree;
    while (*trav != NULL && (*trav)->letter != word[depth]) {
        trav = &((*trav)->newWord);
    }
    
    // If character node found
    if (*trav != NULL) {
        // Recur for the next character
        int shouldDeleteCurrentNode = deleteHelper(&((*trav)->nextLetter), word, depth + 1);
        
        // If child node was deleted and current node has no other children
        if (shouldDeleteCurrentNode && (*trav != NULL) && isNodeEmpty(*trav)) {
            Trie temp = *trav;
            *trav = (*trav)->newWord;
            free(temp);
            return 1; // Current node can be deleted
        }
    }
    
    return 0; // Don't delete current node
}

int deleteWord(Trie* tree, char* word) {
    if (tree == NULL || *tree == NULL || word == NULL) {
        return 0;
    }
    
    return deleteHelper(tree, word, 0);
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
