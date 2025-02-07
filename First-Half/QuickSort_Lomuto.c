#include "header/utils.c"

void quickSort(int *, int, int);
int lomutoPartition(int*,int,int);

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
    int pi = lomutoPartition(arr,low,high);
    quickSort(arr,low,pi-1); 
    quickSort(arr,pi+1,high);
  }
}

int lomutoPartition(int arr[],int low,int high){
  int pivot = arr[high];
  int i = low - 1,j,temp = 0;

  for(j=low;j<high;j++){
    if(arr[j] <= pivot){
      temp = arr[++i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  temp = arr[++i];
  arr[i] = arr[high];
  arr[high] = temp;

  return i;
}
