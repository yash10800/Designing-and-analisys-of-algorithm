#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int other = *a;
    *a = *b;
    *b = other;
}

int Qsort(int l, int r, int arr[], int n) {

    int idx = l, size = (r - l + 1);
    int pivot = l + rand() % size;
    int target = arr[pivot];

    for (int i = l; i <= r; i++) {
        if (target > arr[i]) {
            swap(&arr[i], &arr[idx]);
            idx++;
        }
    }

    if (idx < pivot) {
        swap(&arr[idx], &arr[pivot]);
    }


    //Debug ...

    printf("%d, %d, %d \n", l, r, pivot);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return idx;
}

void partition(int l, int r, int arr[], int n) {
    if (l < r) {
        int parInd = Qsort(l, r, arr, n);
        partition(l, parInd - 1, arr, n);
        partition(parInd + 1, r, arr, n);
    }
}

int main() {
    int n;
    printf("Enter the size of the array : ");
    scanf("%d", &n);
    
    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    partition(0, n - 1, arr, n);

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

}