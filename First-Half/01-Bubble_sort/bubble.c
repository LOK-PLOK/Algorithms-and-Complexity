#include "../../utilities/general.h"
#include "../../utilities/test.h"

void bubbleSort(int arr[], int size);

int main(void){
    
    test_sort_w_size(bubbleSort);
    return 0;
}

void bubbleSort(int arr[], int size){
    int i,j,temp;

    for(i=0;i<size-1;i++){
        for(j=0;j<size-i-1;j++){
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
