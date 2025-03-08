#include "../../utilities/general.h"
#include "../../utilities/test.h"
#include <string.h> // Include string.h for memcpy

void mergeSort(int arr[], int low, int high);
void mergeSortWrapper(int arr[], int size);

int main(void) {
    test_sort_w_size(mergeSortWrapper);
    return 0;
}

void mergeSortWrapper(int arr[], int size) {
    mergeSort(arr, 0, size - 1);
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (high + low) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        // merging process
        int leftSize = mid - low + 1;
        int rightSize = high - mid;

        int left[leftSize];
        int right[rightSize];

        memcpy(left, arr + low, sizeof(int) * leftSize);//---------------| can be done manually
        memcpy(right, arr + mid + 1, sizeof(int) * rightSize);//---------|

        int i = 0;
        int j = 0;
        int arrIndex = low;

        while (i < leftSize && j < rightSize) { //-------------------
            if (right[j] < left[i]) {                               //
                arr[arrIndex++] = right[j++];                       //
            } else {                                                //
                arr[arrIndex++] = left[i++];                        //
            }                                                       //
        }                                                           //
                                                                    // ---> merging process (similar to union but includes duplicates)
        while (i < leftSize) {                                      //
            arr[arrIndex++] = left[i++];                            //
        }                                                           //
                                                                    //
        while (j < rightSize) {                                     //
            arr[arrIndex++] = right[j++];                           //
        }                                                           //
    }//--------------------------------------------------------------
}