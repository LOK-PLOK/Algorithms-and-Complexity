#include "header/utils.c"

void quickSort(int *, int, int);

int main(void) {
  system("cls");
  int array[6] = {10, 7, 8, 9, 1, 5};
  int size = 6;
  printf("Before quicksort: ");
  printArr(array,size);
  quickSort(array, 0, size - 1);
  printf("\nAfter quicksort: ");
  printArr(array, size);

  return 0;
}

void quickSort(int arr[], int low, int high) {  //  Recursive
// check whether if low (MinIndx) it still less than high (MaxIndx)
  if(low < high){ 
    // assign the last element as the pivot element
    int pi = arr[high];
    // getting the partition index, should be -1 at the very first call of the function
    int i = low - 1, j;

    for(j = low; j < high; j++){
      if(arr[j] <= pi){
        i++;
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
    }
    
    // we swap the pivot element to its proper spot/index
    i++;
    int temp2 = arr[i];
    arr[i] = arr[high];
    arr[high] = temp2;

    //sorting left parition and right partiion
    quickSort(arr,low,i-1); // Left
    quickSort(arr,i+1,high);// Right
  }
}