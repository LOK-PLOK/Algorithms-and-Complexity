#include "../../utilities/general.h"
#include "../../utilities/test.h"

void quickSort(int arr[], int low, int high);
void quickSortWrapper(int arr[], int size);

int main(void){
  
  test_sort_w_size(quickSortWrapper);
  return 0;
}

void quickSortWrapper(int arr[], int size) {
    quickSort(arr, 0, size - 1);
}


void quickSort(int arr[], int low, int high) {  
  if(low < high){ 
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

    int pi = i;
    quickSort(arr,low,pi-1); 
    quickSort(arr,pi+1,high);
  }
}

