#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
        int o = *a;
        *a = *b;
        *b = o;
}

int findMedian(int arr[], int l, int r) {
        for (int i = l; i <= r; i++) {
            int minInd = i;
            for (int j = i + 1; j <= r; j++) {
                if (arr[minInd] > arr[j])
                    minInd = j;
            }
            swap(&arr[i], &arr[minInd]);
        }
        int size = (r - l + 1);
        return arr[l + (size / 2)];
}

int place(int arr[], int l, int r) {
        int pivot = arr[r], idx = l;
        for (int i = l; i < r; i++) {
            if (pivot >= arr[i]) {
                swap(&arr[idx++], &arr[i]);
            }
        }
        swap(&arr[r], &arr[idx]);
        return idx;
}

int divide(int arr[], int l, int r, int k) {
        int size = (r - l + 1);
        int groups = (size + 4) / 5;
        int *medians = (int *)malloc(sizeof(int) * groups);
        int idx = 0, low = l;
        while (low + 4 <= r) {
            medians[idx++] = findMedian(arr, low, low + 4);
            low += 5;
        }
        if (low <= r)
            medians[idx] = findMedian(arr, low, r);
        int medOfmed = findMedian(medians, 0, groups - 1);
        int pivot = l;
        for (int i = l + 1; i <= r; i++) {
            if (arr[i] == medOfmed) {
                pivot = i;
                break;
            }
        }
        swap(&arr[r], &arr[pivot]);
        int ind = place(arr, l, r);
        if (ind == k) {
            return arr[ind];
        }
        if (ind < k) {
            return divide(arr, ind + 1, r, k);
        }
        return divide(arr, l, ind - 1, k);
}

int main()  {
        int n, k;
        printf("Enter the # of Elements : ");
        scanf("%d", &n);
        int *arr = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }
        printf("Enter the ith Number : ");
        scanf("%d", &k);
        k--;
        printf("%d", divide(arr, 0, n - 1, k));
        return 0;
}