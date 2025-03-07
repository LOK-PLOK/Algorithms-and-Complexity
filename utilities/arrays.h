#ifndef ARRAY_H
#define ARRAY_H

void print(int arr[], int size) {
    if(size > 0) {
        printf("%d", arr[0]);

        for(int i = 1; i < size; i++) {
            printf(", %d", arr[i]);
        }
    }
    else {
        printf("EMPTY");
    }

    printf("\n");
}

void printinl(int arr[], int size) {
    if(size > 0) {
        printf("%d", arr[0]);

        for(int i = 1; i < size; i++) {
            printf(", %d", arr[i]);
        }
    }
    else {
        printf("EMPTY");
    }
}

#endif