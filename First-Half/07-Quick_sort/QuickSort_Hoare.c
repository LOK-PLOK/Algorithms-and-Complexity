#include "../../utilities/general.h"
#include "../../utilities/test.h"

void quickSort(int arr[], int low, int high);
void quickSortWrapper(int arr[], int size);
int lomuto(int arr[],int low,int high);

int main(void){
  
  test_sort_w_size(quickSortWrapper);
  return 0;
}

void quickSortWrapper(int arr[], int size) {
  quickSort(arr, 0, size - 1);
}

void quickSort(int arr[], int low, int high) {  
  if(low < high){
    int i = low-1,j=low,temp;
    int pivot = arr[high];

    for(;j<high;j++){
      if(arr[j] <= pivot){
        i++;
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
    i++;
    temp = arr[i];
    arr[i] = arr[high];
    arr[high] = temp;

    quickSort(arr,low,i-1);
    quickSort(arr,i+1,high);
  }
}

// int lomuto(int arr[],int low,int high){
//   int pivot = arr[high];
//     int i = low - 1;

//     for (int j = low; j < high; j++) {
//         if (arr[j] <= pivot) {
//             i++;
//             int temp = arr[i];
//             arr[i] = arr[j];
//             arr[j] = temp;
//         }
//     }
//     i++;
//     int temp = arr[i];
//     arr[i] = arr[high];
//     arr[high] = temp;
//     return i;
// }
