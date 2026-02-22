#include <stdio.h>

int findDuplicate(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] == arr[j]) {
                return arr[i];
            }
        }
    }
    return 0; 
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10};
    int size = sizeof(arr) / sizeof(arr[0]);
    printf("%d\n", findDuplicate(arr, size)); 
    return 0;
}