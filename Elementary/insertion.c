#include <stdio.h>

void insertionSortSwap(int arr[], int size) {
    for(int i = 1; i < size; i++) {
        for(int j = i; j > 0 && arr[j] < arr[j - 1]; j--) {
            int temp = arr[j];
            arr[j] = arr[j - 1];
            arr[j - 1] = temp;
        }
    }
}

void insertionSortShit(int arr[], int size) {
    int i,j,key;
    for(i = 1; i< size;i++){
        key = arr[i];
        for(j = i-1; j >= 0 && arr[j] > key; j--){
            arr[j+1] = arr[j];
        }
        arr[j+1] = key;
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {10,7,8,9,1,5};
    int N = sizeof(arr) / sizeof(arr[0]);
    insertionSortSwap(arr, N);
    printf("Sorted array: ");
    printArray(arr, N);
    return 0;
}