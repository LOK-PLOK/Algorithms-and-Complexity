#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node {
    int data;
    struct node* link;
} *List;

/* Function Prototypes */
void initList(List* node);
void clean(List* node);
void insertLast(List* node, int n);
void deleteFirst(List* node);
void display(List node);

void strandSort(List* input, List* result);
void merge(List* strand, List* result);

/* Main Function */
int main() {
    List input; initList(&input);
    List result; initList(&result);
    
    for (int i = 0; i < MAX; i++) {
        insertLast(&input, rand() % 10); 
    }
    
    printf("List before Sort: ");
    display(input);
    
    strandSort(&input, &result); 
    
    printf("List after Sort: ");
    display(result);
    
    clean(&input);
    clean(&result);
    return 0;
}

/* Strand Sort Implementation */
void strandSort(List* input, List* result) {
    while(*input != NULL){
        List strand = NULL;
        insertLast(&strand,(*input)->data);
        deleteFirst(input);
        
        List*trav = input;
        int curr = strand->data;
        while(*trav != NULL){
            if((*trav)->data > curr){
                curr = (*trav)->data;
                insertLast(&strand,curr);
                deleteFirst(trav);
            }else{
                trav = &(*trav)->link;
            }
        }

        merge(&strand,result);
    }
}

/* Merge Function (Now Void) */
void merge(List* strand, List* result) {
    List merged  = NULL, *tail = &merged;
    List A = *strand, B = *result;

    while(A != NULL && B != NULL){
        if(A->data < B->data){
            *tail = A;
            A = A->link;
        }else{
            *tail = B;
            B = B->link;
        }
        tail = &(*tail)->link;
    }
    *tail = (A != NULL)? A:B;
    *result = merged;

}    

/* Deletes First Node */
void deleteFirst(List* node) {
    if (*node != NULL) {
        List temp = *node;
        *node = temp->link;
        free(temp);
    }
}

/* Initializes a List */
void initList(List* node) {
    *node = NULL;
}

/* Inserts at the End of the List */
void insertLast(List* node, int n) {
    List temp = (List)malloc(sizeof(struct node));
    if (temp != NULL) {
        temp->data = n;
        temp->link = NULL;
        
        if (*node == NULL) {
            *node = temp;
        } else {
            List trav = *node;
            while (trav->link != NULL) {
                trav = trav->link;
            }
            trav->link = temp;
        }
    }
}

/* Displays the List */
void display(List node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->link;
    }
    puts("");
}

/* Cleans up Memory */
void clean(List* node) {
    while (*node != NULL) {
        deleteFirst(node);
    }
}
