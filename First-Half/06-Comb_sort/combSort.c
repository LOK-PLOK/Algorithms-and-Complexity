#include "../../utilities/general.h"
#include "../../utilities/test.h"

void combSort(int arr[], int n);

int main(void){
  
  test_sort_w_size(combSort);
  return 0;
}

void combSort(int arr[], int size){
  int gap = size;
  int swapped = 1;
  
  while(gap > 1 || swapped){
    // Update the gap
    gap = (int)gap / 1.3;
    if(gap < 1) gap = 1;
    
    swapped = 0;
    for(int i = 0; i < size - gap; i++){
      if(arr[i] > arr[i + gap]){
        int temp = arr[i];
        arr[i] = arr[i + gap];
        arr[i + gap] = temp;
        swapped = 1;
      }
    }
  }
}