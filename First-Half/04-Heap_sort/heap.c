#include "../../utilities/general.h"
#include "../../utilities/test.h"

void heapSort(int arr[], int n);
void heapifySubtree(int arr[],int lastNdx,int parent);

int main(void){
    
    test_sort_w_size(heapSort);
    return 0;
}

void heapSort(int arr[], int size){
    int i,lastndx = size-1,temp;

    for(i = (lastndx-1)/2; i>=0; i--){
        heapifySubtree(arr,lastndx,i);
    }
    for(i=lastndx; i>0;i--){
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        lastndx--;
        heapifySubtree(arr,lastndx,0);
    }
}

void heapifySubtree(int arr[],int lastNdx,int parent){
    int big,LC,RC,flag=0,temp;

    while(!flag){
        big = parent;
        LC = parent*2+1;
        RC = LC + 1;

        if(LC <= lastNdx && arr[LC] > arr[big]){
            big = LC;
        }

        if(RC <= lastNdx && arr[RC] > arr[big]){
            big = RC;
        }

        if(big != parent){
            temp = arr[big];
            arr[big] = arr[parent];
            arr[parent] = temp;
            parent = big;
        }else{
            flag = 1;
        }
    }
}