#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void printArr(int arr[], int size);

void printArr(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}
