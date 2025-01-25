#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

void printArr(int arr[], int size);

void printArr(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}

int arr1[] = {3, 4, 9, 1, 7, 0, 5, 2, 6, 8};
int arr2[] = {23, 45, 12, 87, 34, 91, 65, 17, 53, 78};
