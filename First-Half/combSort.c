#include "header/utils.c"
#define MAX 10

typedef int List[MAX];

void combSort(List arr,int size);

int main(){
    system("cls");
    List arr = {0};
    for(int i = 0; i<MAX;i++){
        arr[i] = rand() % 10;
    }
    printf("List before Sort: ");
    printArr(arr,MAX);
    printf("List after Sort: ");
    combSort(arr,MAX);
    printArr(arr,MAX);
    
    return 0;
}

void combSort(List arr,int size){
    int i, gap = size,temp;
    int swapped = 1; // Default = TRUE: assumption that it is unsorted

    while(gap != 1 || swapped){
        gap /= 1.3;
        if(gap < 1){
            gap = 1;
        }
        swapped = 0;
        for(i=0;i<size-gap;i++){
            if(arr[i+gap] < arr[i]){
                temp = arr[i+gap];
                arr[i+gap] = arr[i];
                arr[i] = temp;
            }
        }
    }
}


