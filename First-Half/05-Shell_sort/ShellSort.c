#include "../../utilities/general.h"
#include "../../utilities/test.h"

void shellSort(int arr[], int size);

int main(void){
  
  test_sort_w_size(shellSort);
  return 0;
}

void shellSort(int arr[], int size) {  
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

