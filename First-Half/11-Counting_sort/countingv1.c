#include "../../utilities/general.h"
#include "../../utilities/test.h"

void countingSort(int arr[], int n);

int main(void){
  
  test_sort_w_size(countingSort);
  return 0;
}

void countingSort(int arr[], int size) {
    if (size != 0) {
        int i,max = arr[0];

        for(i = 1; i<size;i++){
            if(max < arr[i]){
                max = arr[i];
            }
        }

        int countSize = max + 1;
        int countArr[countSize];
        memset(countArr,0,sizeof(int) * countSize);

        for(i=0;i<size;i++){
            countArr[arr[i]]++;
        }

        for(i=1;i<countSize;i++){
            countArr[i] += countArr[i-1];
        }

        int output[size];
        for(i=0;i<size;i++){
            output[countArr[arr[i]]-1] = arr[i];
            countArr[arr[i]]--;
        }

        for(i=0;i<size;i++){
            arr[i] = output[i];
        }

        // or use memcopy
        // memcpy(arr,output,sizeof(int)*size);
    }
}