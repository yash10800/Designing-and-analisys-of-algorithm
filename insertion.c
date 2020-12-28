#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y) {
    int other = *x;
    *x = *y;
    *y = other;
}

void recur(int idx, int n, int arr[]) {

    if (idx == n) {
        return;
    }

    for (int i = idx; i - 1 >= 0; i--) {
        if (arr[i] < arr[i - 1]) {
            swap(&arr[i], &arr[i - 1]);
        }
        else {
            break;
        }
    }

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

        for (int j = i; j - 1 >= 0; j--) {
            if (arr[j] < arr[j - 1]) {
                swap(&arr[j], &arr[j - 1]);
            }
            else {
                break;
            }
        }
    }
*/
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
