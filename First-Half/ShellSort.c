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

/**
 * Shell Sort implementation.
 *
 * Shell Sort is an in-place comparison-based sorting algorithm that generalizes insertion sort
 * to allow the exchange of items that are far apart. The idea is to arrange the list of elements
 * so that, starting anywhere, taking every Nth element produces a sorted list. Such a list is said
 * to be N-sorted. The algorithm uses a sequence of increments h, which is commonly known as the gap sequence.
 *
 * Time Complexity:
 * - Best Case: O(n log n) when using an optimal gap sequence.
 * - Average Case: O(n^(3/2)) to O(n^(7/6)) depending on the gap sequence.
 * - Worst Case: O(n^2) when using a poor gap sequence.
 *
 * Space Complexity:
 * - O(1) as it is an in-place sorting algorithm.
 *
 * Stability:
 * - Shell Sort is not a stable sorting algorithm.
 *
 * Use Cases:
 * - Shell Sort is useful for medium-sized arrays where the overhead of more complex algorithms
 *   like quicksort or mergesort is not justified.
 * - It is also useful when the array is already partially sorted, as it can perform better than
 *   other O(n^2) algorithms like bubble sort or insertion sort.
 */

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

