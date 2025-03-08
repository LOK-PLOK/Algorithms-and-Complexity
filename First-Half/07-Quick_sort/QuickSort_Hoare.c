#include "../../utilities/general.h"
#include "../../utilities/test.h"

void quickSort(int arr[], int low, int high);
void quickSortWrapper(int arr[], int size);
int hoare(int arr[],int low,int high);

int main(void){
  
  test_sort_w_size(quickSortWrapper);
  return 0;
}

void quickSortWrapper(int arr[], int size) {
  quickSort(arr, 0, size - 1);
}

void quickSort(int arr[], int low, int high) {  
  if(low < high){
    int i = low-1, j = high + 1, pivot = arr[low],temp;

    while(i<j){
      do{
        i++;
      }while(arr[i] < pivot);

      do{
        j--;
      }while(arr[j] > pivot);

      if(i < j){
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }

    quickSort(arr,low,j);
    quickSort(arr,j+1,high);
  }
}

// int hoare(int arr[],int low,int high){
//   int i = low-1,j=high +1,pivot = arr[low],temp;

//   while(i<j){
//     do{
//       i++;
//     }while(arr[i] < pivot);

//     do{
//       j--;
//     }while(arr[j] > pivot);

//     if(i < j){
//       temp = arr[i];
//       arr[i] = arr[j];
//       arr[j] = temp;
//     }
//   }

//   return j;
// }
