#include <stdio.h>

void printArr(int arr[], int size){
    for (int i = 0; i < size; i++){
        printf("%d ", arr[i]);
    }
}

void selectionSort(int arr[], int size){
    for (int i = 0; i < size - 1; i++){
        int minIndex = i;
        for (int j = i + 1; j < size; j++){
            if (arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        int temp = arr[minIndex];
        arr[minIndex] = arr[i];
        arr[i] = temp;
    }
}



int main(){
    int arr[] = {10,7,8,9,1,5};
    int size = sizeof(arr) / sizeof(arr[0]);
    selectionSort(arr,size);
    printArr(arr,size);
    return 0;
}