#include "../../utilities/general.h"
#include "../../utilities/test.h"

void insertionSort(int arr[], int size);

int main(void){
    
    test_sort_w_size(insertionSort);
    return 0;
}

void insertionSort(int arr[], int size){
    int i,j,key;

    for(i=1;i<size;i++){
        key = arr[i];
        for(j=i;j>0 && arr[j-1] > key; j--){
            arr[j] = arr[j-1];
        }
        arr[j] = key;
    }
}
