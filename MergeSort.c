#include <stdio.h>
#include <stdlib.h>

const int N = 500;

void Merge(int l1, int r1, int l2, int r2, int arr[]) {
    // L to Mid, Mid + 1 to R
    int size1 = (r1 - l1 + 1);
    int size2 = (r2 - l2 + 1);
    int *first = (int *)malloc(sizeof(int) * size1);
    int *second = (int *)malloc(sizeof(int) * size2);

    for (int i = l1; i <= r1; i++) {
        first[i - l1] = arr[i];
    }
    for (int i = l2; i <= r2; i++) {
        second[i - l2] = arr[i];
    }
    int ptr0 = 0, ptr1 = 0;
    int idx = l1;
    while (ptr0 < size1 && ptr1 < size2) {
        if (first[ptr0] < second[ptr1]) {
            arr[idx] = first[ptr0++];
        }
        else {
            arr[idx] = second[ptr1++];
        }
        idx++;
    }
    while (ptr0 < size1) {
        arr[idx++] = first[ptr0++];
    }
    while (ptr1 < size2) {
        arr[idx++] = second[ptr1++];
    }
}

void MergeSort(int l, int r, int arr[]) {
    if (l < r) {
        int mid = (l + r) / 2;
        MergeSort(l, mid, arr);
        MergeSort(mid + 1, r, arr);
        Merge(l, mid, mid + 1, r, arr);
    }
}

int main() {
    int *arr = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        arr[i] = rand();
    }
    int Sorted = 0;
    for (int i = 0; i < N; i += 50) {
        int currLeft = i, currRight = i + 49;
        MergeSort(currLeft, currRight, arr);
        if (Sorted != 0) {
            Merge(0, Sorted - 1, currLeft, currRight, arr);
        }
        Sorted += 50;
    }

    // For testing !...
    /*
    for (int i = 1; i < N; i++) {
        if (arr[i] < arr[i - 1]) {
            printf("NO");
            return 0;
        }
    }
    printf("YES");
    */
}
