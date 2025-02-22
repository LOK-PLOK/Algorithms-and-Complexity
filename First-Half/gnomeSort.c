#include "header/utils.c"
#define MAX 10

typedef int List[MAX];

void gnomeSort(List arr,int size);

int main(){
    system("cls");
    List arr = {0};
    for(int i = 0; i<MAX;i++){
        arr[i] = rand() % 10;
    }
    printf("List before Sort: ");
    printArr(arr,MAX);
    printf("List after Sort: ");
    gnomeSort(arr,MAX);
    printArr(arr,MAX);
    
    return 0;
}

void gnomeSort(List arr,int size){
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


