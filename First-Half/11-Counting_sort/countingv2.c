#include "../../utilities/general.h"
#include "../../utilities/test.h"
#define MAX_COUNT_SIZE 100000
void countingSort(int arr[], int n);

int main(void){
  
  test_sort_w_size(countingSort);
  return 0;
}

void countingSort(int arr[], int size) {
    if (size != 0) {
        int i,j;
        int max = arr[0];
        int min = arr[0];

        for(i=0;i<size;i++){
            if(max < arr[i]){
                max = arr[i];
            }

            if(min > arr[i]){
                min = arr[i];
            }
        }

        int countSize = max - min + 1;

        if (countSize > MAX_COUNT_SIZE) {
            printf("\nError: Size is too big. Use another sorting algorithm");
            return;
        }
        int countArr[countSize];
        memset(countArr,0,sizeof(int)*countSize);

        for(i=0;i<size;i++){
            int pos = arr[i] - min;
            countArr[pos]++;
        }

        for(j=countSize-1;j>0;j--){
            countArr[j] = countArr[j-1];
        }
        countArr[0] = 0;

        for(i=1; i < countSize;i++){
            countArr[i] += countArr[i-1];
        }

        int output[size];

        for(i=0;i<size;i++){
            int pos = arr[i] - min;
            output[countArr[pos]++] = arr[i];
        }

        for(i=0;i<size;i++){
            arr[i] = output[i];
        }

        //or use memcopy
        // memcpy(arr,output,sizeof(int)*size);
    }
}