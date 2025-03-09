#include "../../utilities/general.h"
#include "../../utilities/test.h"

void mergeSort(int arr[], int size);

int main() {
    test_sort_w_size(mergeSort);
    return 0;
}

void mergeSort(int arr[], int size) {
    for (int gap = 1; gap < size; gap *= 2) {
        int end = size - gap;
        
        for (int i = 0; i < end; i += (gap * 2)) {
            int l_size = gap;
            int r_size = (gap < size-(gap+i))? (gap):(size-(gap+i));
            int left[l_size];
            int right[r_size];

            memcpy(left, arr + i, sizeof(int) * l_size);
            memcpy(right, arr + i + gap, sizeof(int) * r_size);

            int l_index = 0;
            int r_index = 0;
            int arr_index = i;

            while (l_index < l_size && r_index < r_size) {
                if (right[r_index] < left[l_index]) {
                    arr[arr_index++] = right[r_index++];
                }
                else {
                    arr[arr_index++] = left[l_index++];
                }
            }

            while (l_index < l_size) {
                arr[arr_index++] = left[l_index++];
            }

            while (r_index < r_size) {
                arr[arr_index++] = right[r_index++];
            }
        }
    }
}