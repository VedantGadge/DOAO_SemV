#include <stdio.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int left = low + 1;
    int right = high;
    while (1) {
        while (left <= right && arr[left] < pivot) left++;
        while (left <= right && arr[right] > pivot) right--;
        if (left >= right) break;
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
    swap(&arr[low], &arr[right]);
    return right;
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int p = partition(arr, low, high);
        quick_sort(arr, low, p - 1);
        quick_sort(arr, p + 1, high);
    }
}

int main() {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) return 0;
    int arr[100000];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    quick_sort(arr, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%d", arr[i]);
        if (i + 1 < n) printf(" ");
    }
    return 0;
}