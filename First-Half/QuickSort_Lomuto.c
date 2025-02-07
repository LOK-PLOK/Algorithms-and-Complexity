#include "header/utils.c"

void quickSort(int *, int, int);
int lomutoPartition(int*,int,int);

int main(void) {
  system("clear");
  int array[6] = {10, 7, 8, 9, 1, 5};
  int size = 6;
  printf("Before quicksort: ");
  printArr(array,size);
  quickSort(array, 0, size - 1);
  printf("\nAfter quicksort: ");
  printArr(array, size);
  printf("\n\n");

  return 0;
}



/**
 * Quicksort using Lomuto partition scheme.
 *
 * This function sorts an array of integers in ascending order using the quicksort algorithm.
 * The Lomuto partition scheme is used to partition the array.
 *
 * Time Complexity:
 * - Best Case: O(n log n) when the pivot divides the array into two nearly equal halves.
 * - Average Case: O(n log n) due to the balanced partitioning on average.
 * - Worst Case: O(n^2) when the pivot results in highly unbalanced partitions (e.g., when the array is already sorted).
 *
 * Space Complexity:
 * - O(log n) due to the recursion stack in the best and average cases.
 * - O(n) in the worst case due to the recursion stack when the partitions are highly unbalanced.
 *
 * Stability:
 * - Quicksort is not a stable sorting algorithm.
 *
 * Use Cases:
 * - Quicksort is useful for large datasets where average-case performance is acceptable.
 * - It is also useful when space is limited, as it is an in-place sorting algorithm.
 *
 * @param arr The array of integers to be sorted.
 * @param low The starting index of the array segment to be sorted.
 * @param high The ending index of the array segment to be sorted.
 */

void quickSort(int arr[], int low, int high) {  
  if(low < high){ 
    int pi = lomutoPartition(arr,low,high);
    quickSort(arr,low,pi-1); 
    quickSort(arr,pi+1,high);
  }
}

int lomutoPartition(int arr[],int low,int high){
  int pivot = arr[high];
  int i = low - 1,j,temp = 0;

  for(j=low;j<high;j++){
    if(arr[j] <= pivot){
      temp = arr[++i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  temp = arr[++i];
  arr[i] = arr[high];
  arr[high] = temp;

  return i;
}
