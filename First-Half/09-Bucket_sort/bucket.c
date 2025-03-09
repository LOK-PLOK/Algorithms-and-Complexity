#include "../../utilities/general.h"
#include "../../utilities/test.h"

typedef struct node{
    int data;
    struct node* link;
}*Bucket;

void initList(Bucket* node){
    *node = NULL;
}

void insertSorted(Bucket* node, int elem){
    Bucket* trav, temp;

    for(trav = node; *trav != NULL && (*trav)->data < elem; trav = &(*trav)->link){}

    temp = (Bucket)malloc(sizeof(struct node));
    if(temp != NULL){
        temp->data = elem;
        temp->link = *trav;
        *trav = temp;
    }
}

void deleteNode(Bucket* node){
    Bucket temp;
    if(*node != NULL){
        temp = *node;
        *node = temp->link;
        free(temp);
    }
}

void bucketSort(int arr[], int n);

int main(void){
    test_sort_w_size(bucketSort);
    return 0;
}

void bucketSort(int arr[], int size){
    int max = arr[0];
    int min = arr[0];
    int i = 0, j = 0;
    Bucket trav, temp;

    for(i = 1; i < size; i++){
        if(max < arr[i]){
            max = arr[i];
        }

        if(min > arr[i]){
            min = arr[i];
        }
    }

    int bucketSize = size;
    Bucket local[bucketSize];

    for(i = 0; i < bucketSize; i++){
        local[i] = NULL;
    }

    for(i = 0; i < size; i++){
        int index = (arr[i] - min) * bucketSize / (max - min + 1);
        insertSorted(&local[index], arr[i]);
    }

    for(i = 0; i < bucketSize; i++){
        trav = local[i];
        while(trav != NULL){
            arr[j++] = trav->data;
            temp = trav;
            trav = trav->link;
            free(temp);
        }
    }
}