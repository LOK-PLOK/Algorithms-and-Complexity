#include "../../utilities/general.h"
#include "../../utilities/test.h"
#include <string.h> // Include string.h for memcpy

#define BASE 10

void radixSort(int arr[], int n);

int main(void) {
    test_sort_w_size(radixSort);
    return 0;
}

void radixSort(int arr[], int size) {
    int i, j, max = arr[0], exp;

    // Find the maximum number to know the number of digits
    for (i = 1; i < size; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }

    // Do counting sort for every digit. Note that instead of passing the digit number, exp is passed. exp is 10^i where i is the current digit number
    for (exp = 1; max / exp > 0; exp *= 10) {
        int output[size]; // Output array
        int count[10] = {0}; // Initialize count array with all zeros

        // Store count of occurrences in count[]
        for (i = 0; i < size; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        // Change count[i] so that count[i] now contains the actual position of this digit in output[]
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        // Build the output array
        for (i = size - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        // Copy the output array to arr[], so that arr[] now contains sorted numbers according to the current digit
        for (i = 0; i < size; i++) {
            arr[i] = output[i];
        }

        // or use memcpy
        // memcpy(arr, output, sizeof(int) * size);
    }
}