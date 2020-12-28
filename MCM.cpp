#include <stdio.h>
#include <stdlib.h>

const int INF = 1e7;
struct mats {
    int r, c;  
};

//Global Section!
mats *d;
int **dp, **store, n;

int min(int a, int b) {
    if (a < b)
        return a;
    return b;
}

int getCost(int L, int M, int R) {
    return dp[L][M] + dp[M + 1][R] + (d[L].r * d[M].c * d[R].c);
}

void backtrack(int L, int R) {
        if (L == R) {
            printf("%d", L);
            return;
        }
        int M = store[L][R];
        printf("(");
        backtrack(L, M);
        backtrack(M + 1, R);
        printf(")");
}

int main() {
        scanf("%d", &n);
        
        int *dims = (int *)malloc(sizeof(int) * n);
        for (int i = 0; i < n; i++) {
            scanf("%d", dims + i);
        }
        
        n--;
        d = (mats *)malloc(sizeof(mats) * (n + 1));
        for (int i = 1; i <= n; i++) {
            d[i].r = dims[i - 1], d[i].c = dims[i];
        }
        
        dp = (int **)malloc(sizeof(int *) * (n + 1)); // Best Soln. for (L, R).
        store = (int **)malloc(sizeof(int *) * (n + 1)); // Store MergePoint for (L, R) and helps for backtracking.
        
        for (int i = 0; i <= n; i++) {
            dp[i] = (int *)malloc(sizeof(int) * (n + 1));
            store[i] = (int *)malloc(sizeof(int) * (n + 1));
            for (int j = 0; j <= n; j++)
                dp[i][j] = INF;
        }
        for (int i = 0; i <= n; i++) 
            dp[i][i] = 0;
            
        for (int len = 2; len <= n; len++) {
            for (int L = 1; L + len - 1 <= n; L++) {
                int R = L + len - 1;
                for (int M = L; M < R; M++) {
                    int cost = getCost(L, M, R);
                    if (dp[L][R] > cost) {
                        dp[L][R] = cost;
                        store[L][R] = M;
                    }
                }
            }
        }
        
        printf("%d\n", dp[1][n]);
        backtrack(1, n);
}