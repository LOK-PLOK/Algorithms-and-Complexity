#include "../../utilities/general.h"
#include "../../utilities/test.h"

void selectionSort(int arr[], int size);

int main(void){
    
    test_sort_w_size(selectionSort);
    return 0;
}

void selectionSort(int arr[], int size){
    int i,j,temp;

    for(i=0;i<size-1;i++){
        int min = i;
        for(j=i+1;j<size;j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}
