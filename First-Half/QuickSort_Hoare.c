#include "header/utils.c"

void quickSort(int *, int, int);
int hoarePartition(int*,int,int);

int main(void) {
  system("clear");
  int array[6] = {10, 7, 8, 9, 1, 5};
  int size = 6;
  printf("Before quicksort: ");
  printArr(array,size);
  quickSort(array, 0, size - 1);
  printf("\nAfter quicksort: ");
  printArr(array, size);
  printf("\n\n");

  return 0;
}

void quickSort(int arr[], int low, int high) {  
  if(low < high){ 
    int pi = hoarePartition(arr,low,high);
    quickSort(arr,low,pi); 
    quickSort(arr,pi+1,high);
  }
}

int hoarePartition(int arr[],int start,int end){
  int pivot = arr[start];
  int i = start,j = end;
  int temp;

  while(i<j){
    for(; arr[i] < pivot && i < end; i++){}

    for(; arr[j] > pivot && j > start; j--){}

    if(i<j){
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
  }

    return j;
}
