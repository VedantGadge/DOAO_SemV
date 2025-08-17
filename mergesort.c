#include <stdio.h>
#include <stdlib.h>

void merge(int *arr, int low, int mid, int high) {
    int size = high - low + 1;
    int *merged = (int *)malloc(size * sizeof(int));
    if (!merged) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    int left = low;
    int right = mid + 1;
    int x = 0;
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            merged[x++] = arr[left++];
        } else {
            merged[x++] = arr[right++];
        }
    }
    while (left <= mid) merged[x++] = arr[left++];
    while (right <= high) merged[x++] = arr[right++];
    for (int i = 0; i < size; i++) {
        arr[low + i] = merged[i];
    }
    free(merged);
}

void divide(int *arr, int low, int high) {
    if (low >= high) return;
    int mid = low + (high - low) / 2;
    divide(arr, low, mid);
    divide(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid size\n");
        return 1;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            free(arr);
            return 1;
        }
    }

    printf("Original array:\n");
    printArray(arr, n);

    divide(arr, 0, n - 1);

    printf("Sorted array:\n");
    printArray(arr, n);

    free(arr);
    return 0;
}