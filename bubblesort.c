#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int other = *x;
    *x = *y;
    *y = other;
}

void recur(int idx, int arr[]) {

    if (idx == 0) {
        return;
    }

    for (int i = 0; i + 1 <= idx; i++) {
        if (arr[i] > arr[i + 1]) {
            swap(&arr[i], &arr[i + 1]);
        }
    }
    recur(idx - 1, arr);
}

int main() {

    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    recur(n - 1, arr);
    /*

    for (int i = 0; i + 1 < n; i++) {
        int swaps = 0;
        for (int j = 0; j < n - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swaps++;
            }
        }

        if (!swaps) {
            break;
        }
        printf("Pass : %d, No. of swaps are %d\n",i + 1, swaps);
    }
`   */

    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
