#include "./general.h"
#include "./arrays.h"

#define TEST_MAX_ELEM 100
#define TEST_MAX_CHAR 50

#ifndef SORT_TEST_H
#define SORT_TEST_H


typedef struct {
    char label [TEST_MAX_CHAR];
    int start[TEST_MAX_ELEM];
    int correct[TEST_MAX_ELEM];
    int size;
} Test;

Test tests[] = {
    {"Basic case", {5, 3, 8, 4, 2}, {2, 3, 4, 5, 8}, 5},
    {"Empty array", {}, {}, 0},
    {"One element", {1}, {1}, 1},
    {"Already Sorted", {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, 5},
    {"Reverse Sorted", {9, 7, 5, 3, 1}, {1, 3, 5, 7, 9}, 5},
    {"With Duplicates", {4, 2, 2, 8, 3, 3, 1}, {1, 2, 2, 3, 3, 4, 8}, 7},
    {"Large Numbers", {1000000, 500, 100, 250000}, {100, 500, 250000, 1000000}, 4},
    {"Large Sorted", 
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20},
        20},

    {"Large Reverse Sorted", 
        {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5},
        {5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100},
        20},

    {"Large Random", 
        {42, 99, 7, 68, 23, 57, 12, 88, 33, 74, 15, 92, 5, 66, 28, 100, 1, 51, 39, 81},
        {1, 5, 7, 12, 15, 23, 28, 33, 39, 42, 51, 57, 66, 68, 74, 81, 88, 92, 99, 100},
        20},

    {"Very Large (100 elements)", 
        {42, 99, 7, 68, 23, 57, 12, 88, 33, 74, 15, 92, 5, 66, 28, 100, 1, 51, 39, 81,
            24, 11, 78, 95, 54, 20, 87, 34, 63, 96, 19, 77, 4, 45, 60, 71, 16, 84, 10, 98,
            40, 67, 46, 79, 6, 32, 22, 85, 47, 30, 55, 73, 29, 62, 53, 50, 36, 80, 13, 25,
            38, 21, 72, 31, 49, 35, 90, 9, 3, 14, 27, 26, 37, 94, 43, 93, 56, 97, 2, 8,
            86, 17, 48, 58, 75, 41, 59, 89, 44, 64, 76, 91, 18, 70, 83, 82, 61, 52, 69, 65}, 
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 
            21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 
            61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 
            81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}, 
        100}
};


int test_size = sizeof(tests) / sizeof(tests[0]); 

void test_check(int correct[], int output[], int size, int test_number, char label[]) {
    if(memcmp(correct, output, sizeof(int) * size) == 0) {
        printf("Test #%d Successful! (%s)\n", test_number, label);
    }
    else {
        printf("\nTest #%d Failed! (%s)\n", test_number, label);
        printf("Expected:\t[");
        printinl(correct, size);
        printf("]\nOutput:\t\t[");
        printinl(output, size);
        printf("]\n\n");
    }
}

void test_sort_w_size(void (*sort)(int arr[], int size)) {
    // cls();
    for (int i = 0; i < test_size; i++) {
        Test test = tests[i];         

        int arr[test.size];
        memcpy(arr, test.start, sizeof(int) * test.size);

        sort(arr, test.size);

        test_check(test.correct, arr, test.size, i + 1, test.label);
    }
}

void test_sort_w_low_high(void (*sort)(int arr[], int low, int high)) {
    // cls();
    for (int i = 0; i < test_size; i++) {
        Test test = tests[i];         

        int arr[test.size];
        memcpy(arr, test.start, sizeof(int) * test.size);

        sort(arr, 0, test.size - 1);

        test_check(test.correct, arr, test.size, i + 1, test.label);
    }
}

#endif