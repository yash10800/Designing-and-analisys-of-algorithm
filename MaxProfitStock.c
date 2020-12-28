#include <stdlib.h>
#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    //For any Transaction let's say (i, j) where ith day : buy and jth day : sold stock.
    //For Ai - Aj can be represented in the form of summation of difference of consecutive elements from i to j - 1.
    int *diff = (int *)malloc(sizeof(int) * n);
    for (int i = 1; i < n; i++) {
        diff[i] = arr[i] - arr[i - 1];
    }
    int bestProfit = -1e9;
    int sum = 0;
    for (int i = 1; i < n; i++) {
        sum += diff[i];
        if (bestProfit < sum) {
            bestProfit = sum;
        }
        if (sum < 0) {
            sum = 0;
        }
    }
    printf("%d", bestProfit);
}

/*
17
100 113 110 85 105 102 86 63 81 101 94 106 101 79 94 90 97
*/
