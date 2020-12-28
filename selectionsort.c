#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int other = *x;
    *x = *y;
    *y = other;
}

void recur(int idx, int n, int arr[]) {

    if (idx == n - 1) {
        return;
    }

    int small_idx = idx;

    for (int i = idx; i < n; i++) {
        if (arr[small_idx] > arr[i]) {
            small_idx = i;
        }
    }

    swap(&arr[small_idx], &arr[idx]);

    recur(idx + 1, n, arr);
}

int main() {

    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    recur(0, n, arr);
/*
    for (int i = 0; i < n; i++) {
        int smallest_idx = i;
        for (int j = i; j < n; j++) {
            if (arr[j] < arr[smallest_idx]) {
                smallest_idx = j;
            }
        }
        swap(&arr[i], &arr[smallest_idx]);
    }
*/
    for (int i = 0; i < n; i++) {
        printf("%d ",arr[i]);
    }

    return 0;
}
