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
  if (low < high) {
      int i = low - 1;
      int j = low;
      int pivot = arr[high];

      for (; j < high; j++) {
          if (arr[j] < pivot) {
              swap(arr + (++i), arr + j);
          }
      }

      swap(arr + (++i), arr + high);

      quickSort(arr, low, i - 1);
      quickSort(arr, i + 1, high);
  }
}

