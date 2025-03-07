#include "../../utilities/general.h"
#include "../../utilities/test.h"

void gnomeSort(int arr[], int n);

int main(void){
  
  test_sort_w_size(gnomeSort);
  return 0;
}

void gnomeSort(int arr [],int size){
    int i = 1,temp;

    while(i<size){
        if(arr[i] < arr[i-1]){
            temp = arr[i];
            arr[i] = arr[i-1];
            arr[i-1] = temp;
            if(i > 1){
                i--;
            }
        }else{
            i++;
        }
    }
}


