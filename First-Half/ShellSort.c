#include "header/utils.c"

void shellSort(int *, int);

int main(void) {
  system("clear");
  int array[6] = {10, 7, 8, 9, 1, 5};
  int size = 6;
  printf("Before shellSort: ");
  printArr(array, size);
  shellSort(array, size);
  printf("\nAfter shellSort: ");
  printArr(array, size);
  printf("\n\n");

  return 0;
}

void shellSort(int arr[], int n) {  
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

