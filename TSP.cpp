#include <stdio.h>

int min(int a, int b) {
    if (a > b)
        return b;
    return a;
}

const int N = 20, INF = 1e5;
int cost[N][N], dp[N][1LL << N], cities;

int solve(int city, int mask) {
    int value = (1LL << cities) - 1;
    if (value == mask) {
        return cost[city][0];
    }
    int cur = dp[city][mask];
    if (cur != -1) {
        return cur;
    }
    cur = INF;
    for (int v = 0; v < cities; v++) {
        if ((mask & (1LL << v)) == 0) {
            cur = min(cur, cost[city][v] + solve(v, (mask | (1LL << v))));
        }
    }
    return dp[city][mask] = cur;
}

int main() {
    int roads;
    printf("Enter the number of Cities : \n");
    scanf("%d", &cities);
    printf("Enter the number of Roads : \n");
    scanf("%d", &roads);
    
    for (int i = 0; i < cities; i++)
        for (int j = 0; j < cities; j++)
            cost[i][j] = INF;
            
    for (int i = 0; i < cities; i++)
        for (int j = 0; j < (1LL << cities); j++)
            dp[i][j] = -1;
            
    for (int i = 0; i < roads; i++) {
        int u, v, length;
        scanf("%d%d%d", &u, &v, &length);
        u--; v--;
        cost[u][v] = cost[v][u] = length;
    }
    
    int ans = solve(0, 1);
    printf("Minimum Cost : %d", ans);
}

/*
4 6
1 2 10
1 4 20
1 3 15
2 3 35
2 4 25
3 4 30
*/